#include <stdio.h>
#include <stdlib.h>    // atoi, malloc, abs, srand, _Exit, EXIT_SUCCESS/FAILURE
#include <time.h>      // time
#include <sys/types.h> // pid_t
#include <sys/wait.h>  // wait
#include <errno.h>     // errno
#include <fcntl.h>     // pipe flags
#include <unistd.h>    // fork
#include <queue>
#include "test_suite.h"
#include "environ.h"   // detectCPU, detectSIMD

#include <iostream>
using std::cout;
using std::endl;


// Number and offset of elements to process
int num_elems = 0;
int offset_elems = 0;


int main(int argc, char *argv[])
{
    if (argc > 1)
        num_elems = atoi(argv[1]);
    if (argc > 2)
        offset_elems = atoi(argv[2]);

    const int NUM_TESTS = sizeof(TESTS) / sizeof(struct TEST_T);
    const int NUM_WORKERS = (MAX_WORKERS > NUM_TESTS) ? (NUM_TESTS) : (MAX_WORKERS);

    // Seed RNG
    srand(time(NULL));

    cout << "SIMD TESTSUITE (" << SIMD_WIDTH_BITS << "-bits)" << endl;
    detectCPU();
    detectSIMD();

    if (test_suite(TESTS, NUM_TESTS, NUM_WORKERS))
        _Exit(EXIT_FAILURE);

    return EXIT_SUCCESS;
}


// NOTE: For portability it is recommended to use fork or pthreads.
// Fork is preferred to prevent child process errors
// from affecting the parent process.


// Pipe management constants
// TODO: need to move this somewhere else?
enum PIPE_PORTS { PIPE_READ_PORT = 0, PIPE_WRITE_PORT, NUM_PIPE_PORTS };
// NOTE: FAILED_TEST not used, instead -test_id is used since it identifies each test.
//       CANCEL_TEST is used as signal from manager-to-workers.
//       SUCCESS_TEST is used as signal from workers-to-manager, has to be 0
//       because of no-sign property (for failed tests) and is used as an accumulator
enum PIPE_MSGS { FAILED_TEST = -1, CANCEL_TEST = 0, SUCCESS_TEST = 0 };


/*!
 *  \brief Test suite framework
 *
 *  Runs test cases and their validation in independent processes.
 *  The test suite framework manages the scheduling and task distribution.
 */
int test_suite(const struct TEST_T * const tests, const int num_tests, const int num_workers)
{
    int manager_to_worker[NUM_PIPE_PORTS];
    int worker_to_manager[NUM_PIPE_PORTS];
    const pid_t manager_pid = getpid();
    pid_t worker_pid = (pid_t)-1;

    // Create unnamed and blocking pipes for IPC
    if (pipe2(manager_to_worker, 0) == -1) {
        cout << "(MANAGER " << manager_pid << ") ERROR: failed to create manager to worker pipe" << endl;
        return -1;
    }
    if (pipe2(worker_to_manager, 0) == -1) {
        cout << "(MANAGER " << manager_pid << ") ERROR: failed to create worker to manager pipe" << endl;
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
    else if (!worker_pid) {

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

        // _Exit does not call any functions registered with atexit() or on_exit().
        // Close file descriptors (may flush I/O buffers and remove temporary files)
        _Exit(EXIT_SUCCESS);
    }

    return 0;
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
            //cout << "(WORKER  " << worker_pid << ") Running test " << current_test << " ... " << tests[current_test - 1].test_name << endl;

            // Run test
            int test_result = SUCCESS_TEST;
            for (int i = 0; i < RUNS_PER_TEST; ++i)
                test_result += tests[current_test - 1].test_func(num_elems, offset_elems);

            // Validate test
            if (test_result != SUCCESS_TEST) {
                cout << "(WORKER  " << worker_pid << ") FAILED test " << current_test << " ... " << tests[current_test - 1].test_name << endl;
                //current_test = FAILED_TEST;
                current_test = -current_test;
            }
            else {
                cout << "(WORKER  " << worker_pid << ") PASSED test " << current_test << " ... " << tests[current_test - 1].test_name << endl;
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
    int current_test = 0;

    // Array has 1 more than number of tests since test IDs are offset by 1.
    // Use entry 0 for global test results calculated by manager process.
    int *test_results = (int *)malloc((num_tests + 1) * sizeof(int));

    cout << "(MANAGER " << manager_pid << ") Total tests = " << num_tests << endl;
    cout << "(MANAGER " << manager_pid << ") Total workers = " << num_workers << endl;

    // Send test IDs to all workers
    for (current_test = 1; current_test <= num_workers; ++current_test) {
        write(manager_to_worker[PIPE_WRITE_PORT], &current_test, sizeof(int));
    }

    // Get test result from workers
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

    // Summarize results from tests
    int tests_passed = 0;
    for (int i = 1; i <= num_tests; ++i) {
        if (test_results[i] > 0)
            tests_passed++;
    }
    cout << "(MANAGER " << manager_pid << ") Successful tests ... " << tests_passed << " of " << num_tests << endl;
    test_results[0] = (tests_passed == num_tests) ? (SUCCESS_TEST) : (FAILED_TEST);

    free(test_results); test_results = NULL;

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
    pid_t *workers = (pid_t *)malloc(num_workers * sizeof(pid_t));

    // Spawn pool of worker processes
    for (int current_worker = 0; current_worker < num_workers; ++current_worker) {

        worker_pid = fork();

        // Cancel active workers
        if (worker_pid < 0) {
            cout << "(MANAGER " << manager_pid << ") ERROR: failed to fork worker #" << current_worker + 1 << endl;
            cancel_workers(manager_to_worker, current_worker);
            break;
        }
        // Worker process
        // Break out of loop to prevent recursive forks
        else if (!worker_pid)
            break;
        else
            workers[current_worker] = worker_pid;
    }

    free(workers); workers = NULL;

    return worker_pid;
}


int cancel_workers(int * const manager_to_worker, const int num_workers)
{
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
        cout << "(MANAGER " << manager_pid << ") Worker " << wait_pid << " completed" << endl;
    }

    return 0;
}

