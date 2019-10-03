#ifndef _COMPILER_VERSIONS_H
#define _COMPILER_VERSIONS_H


/*
 *  Identify compiler and find version as an integer representation
 *  \note Not all compilers represent versions as single integers
 *  \note https://sourceforge.net/p/predef/wiki/Compilers/
 *  \todo Separate architecture from compiler
 */

// Clang
// NOTE: I used same version format as GNUC, need to verify
#if defined(__clang__)
#   define CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)  // VVRPP

// Intel C/C++
#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
#   define INTEL_VERSION (__INTEL_COMPILER)  // VRP

// GNU C/C++ powerPC
#elif defined(__PPC__)
#   error "PowerPC compiler/architecture is not supported."

// Portland Group C++
// NOTE: Imitated GNUC, need to verify
#elif defined(__PGI)
#   define PGI_VERSION (__PGIC__ * 10000 + __PGIC_MINOR__ * 100 + __PGIC_PATCHLEVEL__)  // VVRPP
#   error "PGI compiler/architecture is not supported."

// IBM XL C++ or IBM z/OS XL C++
#elif defined(__IBMCPP__)
#   if defined(__COMPILER_VER__)
#       define IBM_VERSION (__IBMCPP__)  // NVRRP
#   else
#       define IBM_VERSION (__IBMCPP__)  // VRP
#   endif
#   error "IBM compiler/architecture is not supported."

// Microsoft Visual C++
#elif defined(_MSC_VER)
#   if defined(_MSC_FULL_VER)
#       define MSC_VERSION (_MSC_FULL_VER)  // VVRRPPPP
#   else
#       define MSC_VERSION (_MSC_VER)  // VVRR
#   endif
#   error "MSC compiler/architecture is not supported."

// GNU C/C++
// NOTE: This compiler check is last because the meaning of the __GNUC__ macro
//       has changed subtly over the years, from identifying the GNU C/C++
//       compiler to identifying any compiler that implements the GNU compiler extensions.
//       Need to check the use of GCC_VERSION.
#elif defined(__GNUC__)
#   if defined(__GNUC_PATCHLEVEL__)
#       define GNUC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)  // VVRPP
#   else
#       define GNUC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)  // VRR00
#   endif
#else
#   error "Unknown compiler/architecture is not supported."
#endif


#endif  // _COMPILER_VERSIONS_H

