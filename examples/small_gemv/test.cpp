/*
 * Matrix-vector multiply
 *
 * Information on Intel vector pragmas is available in the following link:
 * https://software.intel.com/en-us/cpp-compiler-developer-guide-and-reference-vector-1#58209E46-70EA-4C47-BED6-E69236C6680C
 */

// https://en.cppreference.com/w/cpp/memory/c/aligned_alloc
#include <cstdlib>  // aligned_alloc (C++11), std::aligned_alloc (C++17)
#include <ctime>
#include <iostream>
#include <vector>
#include <boost/align/aligned_allocator.hpp>
#include <cmath>
// #include "papi.h"
#include "simd.h"
#include "environ.h"
#include "utils.h"
#include "vutils.h"


///////////////////////////////////////////////////////////////////////////////
// USER CONFIGURATION
///////////////////////////////////////////////////////////////////////////////
// Square matrix dimension
const size_t N = 6;

// Precision for floating-point operations
// Valid values are: 4, 8
#define REAL_TYPE 4


///////////////////////////////////////////////////////////////////////////////
// FP and SIMD
///////////////////////////////////////////////////////////////////////////////
// Precision for floating-point operations
#if REAL_TYPE == 4
typedef float real;
typedef SIMD_FLT vreal;
#elif REAL_TYPE == 8
typedef double real;
typedef SIMD_DBL vreal;
#endif

// Number of floating-point values that fit into a SIMD register
const int SIMD_STREAMS = SIMD_WIDTH_BYTES / sizeof(real);
const int LOG2STREAMS = std::log2(SIMD_STREAMS);


///////////////////////////////////////////////////////////////////////////////
// PROGRAM
///////////////////////////////////////////////////////////////////////////////
template <typename T>
using aligned_vector = std::vector<T, boost::alignment::aligned_allocator<T, SIMD_WIDTH_BYTES>>;


void gemv(
    const size_t n,
    const size_t lda,
    const aligned_vector<real> v1,
    const aligned_vector<real> v2,
    aligned_vector<real> &dp)
{
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            dp[row] += v1[row * lda + col] * v2[col];
        }
    }
}


void gemv_simd_tree_sum(
    const size_t n,
    const size_t lda,
    const real *v1,
    const real *v2,
    real *dp)
{
#if defined(__INTEL_COMPILER)
    __assume_aligned(v1, SIMD_WIDTH_BYTES);
    __assume_aligned(v2, SIMD_WIDTH_BYTES);
    const real *_v1 = v1;
    const real *_v2 = v2;
#elif defined(__GNUC__)
    const real *_v1 = (real *)__builtin_assume_aligned(v1, SIMD_WIDTH_BYTES);
    const real *_v2 = (real *)__builtin_assume_aligned(v2, SIMD_WIDTH_BYTES);
#endif

    for (size_t row = 0; row < n; row++) {
        vreal vdp = simd_zero();
        for (size_t col = 0; col < lda; col+=SIMD_STREAMS) {
            vreal vv1 = simd_load(&_v1[row * lda + col]);
            vreal vv2 = simd_load(&_v2[col]);
#if defined(__FMA__)
            vdp = simd_fmadd(vv1, vv2, vdp);
#else
            vv1 = simd_mul(vv1, vv2);
            vdp = simd_add(vv1, vdp);
#endif
        }

        // Binary tree sum reduction
        for (size_t i = 0; i < LOG2STREAMS - 1; i++) {
            vdp = simd_hadd(vdp, vdp);
        }

        real tdp[SIMD_STREAMS] __attribute__((aligned(SIMD_WIDTH_BYTES)));
        simd_store(tdp, vdp);
        // NOTE: 'dp' does need to be aligned because it is used to store a scalar value.
#if SIMD_WIDTH_BITS == 128
        // HADD from SSE3 does not interleave horizontal sums.
        dp[row] = tdp[0] + tdp[1];
#else
        dp[row] = tdp[0] + tdp[SIMD_STREAMS / 2];
#endif
    }
}


void print_matrix(
    const size_t n,
    const size_t m,
    const size_t lda,
    const vector<real> v)
{
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < m; col++) {
            std::cout << v[row * lda + col] << ", ";
        }
        std::cout << std::endl;
    }

}


int main(int argc, char *argv[])
{
    int result = 0;

    size_t num_matrices = 1;
    if (argc > 1) {
        num_matrices = std::atoi(argv[1]);
    }

    detectCPU();
    detectSIMD();

    std::cout << "Alignment: " << SIMD_WIDTH_BYTES << std::endl;
    std::cout << "Num. elems: " << SIMD_STREAMS << std::endl;

    // Number of elements in padded matrix column to conform with SIMD alignment
    const size_t lda = (((N * sizeof(real)) / SIMD_WIDTH_BYTES) * SIMD_WIDTH_BYTES + SIMD_WIDTH_BYTES) / sizeof(real);
    // For unaligned rows, set LDA to N
    // const size_t lda = N;

    // Create a vector of given size
    aligned_vector<real> v1(N * lda);      // matrix
    aligned_vector<real> v2(1 * lda, 1.);  // column vector, set to 1 --> add rows of matrix
    aligned_vector<real> dp(N, 0);  // resulting column vector (dot products)

    // Zero out extra rows used for padding, to prevent floating-point exception during vector multiplication.
    // This memory elements are never modified, so set once.
    memset(v2.data() + N, 0, (lda - N) * sizeof(real));

    real *arr_A = NULL, *arr_B = NULL, *arr_C = NULL;
    // scalar_malloc(&arr_A, SIMD_WIDTH_BYTES, SIMD_STREAMS);
    // scalar_malloc(&arr_B, SIMD_WIDTH_BYTES, SIMD_STREAMS);
    // scalar_malloc(&arr_C, SIMD_WIDTH_BYTES, SIMD_STREAMS);

    for (int i = 0; i < SIMD_STREAMS; ++i) {
        arr_A[i] = 1.;
        arr_B[i] = (real)i;
    }

    vreal va = simd_load(arr_A);
    vreal vb = simd_load(arr_B);
    vreal vc = simd_add(va, vb);
    simd_store(arr_C, vc);

    for (int i = 0; i < SIMD_STREAMS; ++i) {
        if (arr_C[i] != (arr_A[i] + arr_B[i]))
            result += 1;
        else
            std::cout << arr_C[i] << std::endl;
    }

    scalar_free(&arr_A);
    scalar_free(&arr_B);
    scalar_free(&arr_C);

    return result;
}
