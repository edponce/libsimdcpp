/*
 * Matrix-vector multiply
 *
 * Information on Intel vector pragmas is available in the following link:
 * https://software.intel.com/en-us/cpp-compiler-developer-guide-and-reference-vector-1#58209E46-70EA-4C47-BED6-E69236C6680C
 */

// https://en.cppreference.com/w/cpp/memory/c/aligned_alloc
#include <cstdlib>  // aligned_alloc (C++11), std::aligned_alloc (C++17)
#include <cstring>
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
    // const real *_v1 = v1; __SIMD_ASSUME_ALIGNED__(v1);
    // const real *_v2 = v2; __SIMD_ASSUME_ALIGNED__(v2);
    const real *_v1 = (real *)__SIMD_ASSUME_ALIGNED__(v1);
    const real *_v2 = (real *)__SIMD_ASSUME_ALIGNED__(v2);

    for (size_t row = 0; row < n; row++) {
        vreal vdp;
        simd_set_zero(&vdp);
        for (size_t col = 0; col < lda; col+=SIMD_STREAMS) {
            vreal vv1 = simd_load(&_v1[row * lda + col]);
            vreal vv2 = simd_load(&_v2[col]);
            vdp = simd_fmadd(vv1, vv2, vdp);
        }

        // Binary tree sum reduction
        for (size_t i = 0; i < LOG2STREAMS - 1; i++) {
            vdp = simd_hadd(vdp, vdp);
        }

        real tdp[SIMD_STREAMS] __SIMD_ALIGN__;
        simd_store(tdp, vdp);
        // NOTE: 'dp' does need to be aligned because it is used to store a scalar value.
        if (SIMD_WIDTH_BYTES == 16) {
            // HADD from SSE3 does not interleave horizontal sums.
            dp[row] = tdp[0] + tdp[1];
        } else if (SIMD_WIDTH_BYTES == 32) {
            dp[row] = tdp[0] + tdp[SIMD_STREAMS / 2];
        }
    }
}


void print_matrix(
    const size_t n,
    const size_t m,
    const size_t lda,
    const real *v)
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
    size_t num_matrices = 1;
    if (argc > 1) {
        num_matrices = std::atoi(argv[1]);
    }

    detectCPU();
    detectSIMD();

    std::cout << "Alignment: " << SIMD_WIDTH_BYTES << std::endl;
    std::cout << "Num. elems: " << SIMD_STREAMS << std::endl;
    std::cout << "Log2 SIMD: " << LOG2STREAMS << std::endl;

    // Number of elements in padded matrix column to conform with SIMD alignment
    const size_t lda = (((N * sizeof(real)) / SIMD_WIDTH_BYTES) * SIMD_WIDTH_BYTES + SIMD_WIDTH_BYTES) / sizeof(real);
    // For unaligned rows, set LDA to N
    // const size_t lda = N;

    // Create a vector of given size
    aligned_vector<real> v1(N * lda);      // matrix
    aligned_vector<real> v2(1 * lda, 1.);  // column vector, set to 1 --> add rows of matrix
    aligned_vector<real> dp(N, 0.);  // resulting column vector (dot products)

    // Zero out extra rows used for padding, to prevent floating-point exception during vector multiplication.
    // This memory elements are never modified, so set once.
    std::memset(v2.data() + N, 0, (lda - N) * sizeof(real));

    // real *v1 = NULL;
    // real *v2 = NULL;
    // real *dp = NULL;
    // scalar_malloc(&v1, SIMD_WIDTH_BYTES, N * lda);
    // scalar_malloc(&v2, SIMD_WIDTH_BYTES, 1 * lda);
    // scalar_malloc(&dp, SIMD_WIDTH_BYTES, N);

    for (size_t k = 0; k < num_matrices; k++) {

        // Initialize vector
        for (size_t row = 0; row < N; row++) {
            for (size_t col = 0; col < N; col++) {
                v1[row * lda + col] = k + 1. * (row + col);
            }
        }

#if defined(DEBUG)
        // Print matrix and vector
        std::cout << "Matrix:" << std::endl;
        print_matrix(N, lda, lda, v1.data());
        std::cout << std::endl;

        std::cout << "Vector:" << std::endl;
        print_matrix(lda, 1, 1, v2.data());
        std::cout << std::endl;
#endif

        // Matrix-vector multiply
        gemv_simd_tree_sum(N, lda, v1.data(), v2.data(), dp.data());
        gemv(N, lda, v1, v2, dp);

#if defined(DEBUG)
        // Print resulting column vector
        std::cout << "Result:" << std::endl;
        print_matrix(N, 1, 1, dp.data());
        std::cout << std::endl;
#endif
    }

    std::cout << "Matrix size: " << N << " x " << lda << std::endl;

    // Only needed if this array was allocated using 'scalar_malloc'.
    // scalar_free(&v1);
    // scalar_free(&v2);
    // scalar_free(&dp);
}
