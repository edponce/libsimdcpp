#include <stdio.h>
#include <stdlib.h>    // malloc, abs, srand
#include <time.h>      // time
#include <sys/types.h> // wait
#include <sys/wait.h>  // wait
#include <errno.h>     // errno
#include <fcntl.h>     // pipe flags
#include <unistd.h>    // fork
#include <queue>
#include "test_suite.h"


int main()
{
    int retval = 0;
    const int NUM_TESTS = sizeof(TESTS) / sizeof(struct TEST_T);
    const int NUM_WORKERS = (MAX_WORKERS > NUM_TESTS) ? (NUM_TESTS) : (MAX_WORKERS);

    // Seed RNG
    srand(time(NULL));

    printf("SIMD TESTSUITE\n");
    retval = test_suite(TESTS, NUM_TESTS, NUM_WORKERS);

    return retval;
}


// NOTE: For portability it is recommended to use fork or pthreads.
// Fork is preferred to prevent child process errors
// from affecting the parent process.


// Pipe management constants
enum PIPE_PORTS { PIPE_READ_PORT = 0, PIPE_WRITE_PORT, NUM_PIPE_PORTS };
// NOTE: Both have to be 0 because of no-sign property and used as accumulator
// NOTE: need to move this somewhere accessible for everyone
enum PIPE_MSGS { FAILED_TEST = -1, CANCEL_TEST = 0, SUCCESS_TEST = 0 };


/*!
 *  \brief Test suite framework
 *
 *  Runs test cases and their validation in independent processes.
 *  The test suite framework manages the scheduling and task distribution.
 */
int test_suite(const struct TEST_T * const tests, const int num_tests, const int num_workers)
{
    int retval = 0;
    int manager_to_worker[NUM_PIPE_PORTS];
    int worker_to_manager[NUM_PIPE_PORTS];
    const pid_t manager_pid = getpid();
    pid_t worker_pid = (pid_t)-1;

    // Create unnamed and blocking pipes for IPC
    if (pipe2(manager_to_worker, 0) == -1) {
        printf("(MANAGER %d) ERROR: failed to create manager to worker pipe\n", manager_pid);
        return -1;
    }
    if (pipe2(worker_to_manager, 0) == -1) {
        printf("(MANAGER %d) ERROR: failed to create worker to manager pipe\n", manager_pid);
        return -1;
    }

    // Spawn worker processes
    worker_pid = create_workers(manager_to_worker, num_workers);

    // Manager process
    if (worker_pid > 0) {

        // Free/close unused resources
        close(worker_to_manager[PIPE_WRITE_PORT]);
        close(manager_to_worker[PIPE_READ_PORT]);

        manager_main(manager_to_worker, worker_to_manager, num_tests, num_workers);

        // Free/close used resources
        close(worker_to_manager[PIPE_READ_PORT]);
        close(manager_to_worker[PIPE_WRITE_PORT]);
    }
    // Worker process
    else if (worker_pid == 0) {

        // Free/close unused resources
        close(worker_to_manager[PIPE_READ_PORT]);
        close(manager_to_worker[PIPE_WRITE_PORT]);

        worker_main(manager_to_worker, worker_to_manager, tests, num_tests);

        // Free/close used resources
        close(worker_to_manager[PIPE_WRITE_PORT]);
        close(manager_to_worker[PIPE_READ_PORT]);

        // Flush C user-space buffers to disk
        // Flush kernel buffers to disk
        fflush(stdout);
        fsync(fileno(stdout));

        // _exit does not call any functions registered with atexit() or on_exit().
        // Close file descriptors (may flush I/O buffers and remove temporary files)
        _exit(0);
    }

    return retval;
}


/*! \brief Entry function for worker processes.
 *
 *  An input and output pair of IPC mechanisms are passed as arguments.
 */
int worker_main(int * const manager_to_worker, int * const worker_to_manager, const struct TEST_T * const tests, const int num_tests)
{
    const pid_t worker_pid = getpid();
    int current_test = CANCEL_TEST;

    // Receive test ID from manager
    read(manager_to_worker[PIPE_READ_PORT], &current_test, sizeof(int));

    // Loop until worker is cancelled
    while (current_test != CANCEL_TEST) {

        // Validate test ID
        if (current_test > 0 && current_test <= num_tests) {
            //printf("(WORKER  %d) Running test %d ... %s\n", (int)worker_pid, current_test, tests[current_test - 1].test_name);

            // Run test
            int test_result = SUCCESS_TEST;
            for (int i = 0; i < MAX_RUNS_PER_TEST; ++i)
                test_result += tests[current_test - 1].test_func();

            // Validate test
            if (test_result != SUCCESS_TEST) {
                printf("(WORKER  %d) FAILED test %d ... %s\n", (int)worker_pid, current_test, tests[current_test - 1].test_name);
                current_test = -current_test;
            }
            else {
                printf("(WORKER  %d) PASSED test %d ... %s\n", (int)worker_pid, current_test, tests[current_test - 1].test_name);
            }
        }

        // Send test result ID to manager
        write(worker_to_manager[PIPE_WRITE_PORT], &current_test, sizeof(int));

        // Receive test ID from manager
        read(manager_to_worker[PIPE_READ_PORT], &current_test, sizeof(int));
    }

    return 0;
}


/*!
 *  \brief Distributes tests among workers using a fair approach.
 *  FCFS (first-come, first-served)
 */
int manager_main(int * const manager_to_worker, int * const worker_to_manager, const int num_tests, const int num_workers)
{
    const pid_t manager_pid = getpid();
    int current_test = CANCEL_TEST;

    // Plus 1 since test IDs are offset by 1.
    // Use entry 0 for status of manager process.
    int *test_results = (int *)malloc((num_tests + 1) * sizeof(int));
    test_results[0] = SUCCESS_TEST;

    printf("(MANAGER %d) Total tests = %d\n", manager_pid, num_tests);
    printf("(MANAGER %d) Total workers = %d\n", manager_pid, num_workers);

    // Send test IDs to all workers
    for (current_test = 1; current_test <= num_workers; ++current_test) {
        write(manager_to_worker[PIPE_WRITE_PORT], &current_test, sizeof(int));
    }

    // Get test result from worker
    // Send new test ID
    for (; current_test <= num_tests; ++current_test) {
        int test_result;
        read(worker_to_manager[PIPE_READ_PORT], &test_result, sizeof(int));
        test_results[abs(test_result)] = test_result;
        write(manager_to_worker[PIPE_WRITE_PORT], &current_test, sizeof(int));
    }

    // Get test result from workers
    for (int current_worker = 0; current_worker < num_workers; ++current_worker) {
        int test_result;
        read(worker_to_manager[PIPE_READ_PORT], &test_result, sizeof(int));
        test_results[abs(test_result)] = test_result;
    }

    // Cancel active workers
    cancel_workers(manager_to_worker, num_workers);

    free(test_results);

    return 0;
}


/*!
 *  Create pool of worker processes to run test cases.
 *  Tests are accessed via an array of function pointers.
 *
 *  Use pipe for inter-process communication. Pipes provide support
 *  for critical section which is used to control the number of tests
 *  remaining to run.
 *
 *  Test IDs start at 1 to allow +- symmetry for error handling.
 */
pid_t create_workers(int * const manager_to_worker, const int num_workers)
{
    const pid_t manager_pid = getpid();;
    pid_t worker_pid = (pid_t)-1;
    pid_t * const workers = (pid_t *)malloc(num_workers * sizeof(pid_t));

    // Spawn pool of worker processes
    for (int current_worker = 0; current_worker < num_workers; ++current_worker) {

        worker_pid = fork();

        // Cancel active workers
        if (worker_pid < 0) {
            printf("(MANAGER %d) ERROR: failed to fork worker #%d\n", manager_pid, current_worker + 1);
            cancel_workers(manager_to_worker, current_worker);
            break;
        }
        // Worker process
        // Break out of loop to prevent recursive forks
        else if (worker_pid == 0)
            break;
        else
            workers[current_worker] = worker_pid;
    }

    free(workers);

    return worker_pid;
}


int cancel_workers(int * const manager_to_worker, const int num_workers)
{
    int retval = 0;
    const pid_t manager_pid = getpid();;

    // Cancel active workers
    //for (int previous_worker = current_worker - 1; previous_worker >= 0; --previous_worker) {
    for (int current_worker = 0; current_worker < num_workers; ++current_worker) {
        const int current_test = CANCEL_TEST;
        write(manager_to_worker[PIPE_WRITE_PORT], &current_test, sizeof(int));
    }

    // Wait for active workers to complete
    //for (int previous_worker = current_worker - 1; previous_worker >= 0; --previous_worker) {
    for (int current_worker = 0; current_worker < num_workers; ++current_worker) {
        int worker_status = 0;
        pid_t wait_pid = waitpid(-1, &worker_status, WUNTRACED | WCONTINUED);
        printf("(MANAGER %d) Worker %d completed\n", manager_pid, wait_pid);
    }

    return retval;
}

