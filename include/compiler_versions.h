#ifndef _COMPILER_VERSIONS_H
#define _COMPILER_VERSIONS_H


/*
 *  Identify compiler version using an integer representation
 *  NOTE: https://sourceforge.net/p/predef/wiki/Compilers/
 */

// LLVM
#if defined(__llvm__)
#   define LLVM_VERSION (0)

// Clang
// NOTE: Imitated GNUC, need to verify
#elif defined(__clang__)
#   define CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)  // VVRPP

// Intel C/C++
#elif defined(__INTEL_COMPILER) || defined(__INTEL_CLANG_COMPILER)
#   define INTEL_VERSION (__INTEL_COMPILER)  // VRP

// Portland Group C++
// NOTE: Imitated GNUC, need to verify
#elif defined(__PGI)
#   define PGI_VERSION (__PGIC__ * 10000 + __PGIC_MINOR__ * 100 + __PGIC_PATCHLEVEL__)  // VVRPP

// IBM XL C++ or IBM z/OS XL C++
#elif defined(__IBMCPP__)
#   if defined(__COMPILER_VER__)
#       define IBM_VERSION (__IBMCPP__)  // NVRRP
#   else
#       define IBM_VERSION (__IBMCPP__)  // VRP
#   endif

// Microsoft Visual C++
#elif defined(_MSC_VER)
#   if defined(_MSC_FULL_VER)
#       define MSC_VERSION (_MSC_FULL_VER)  // VVRRPPPP
#   else
#       define MSC_VERSION (_MSC_VER)  // VVRR
#   endif

// GNU C/C++
// NOTE: Notice that the meaning of the __GNUC__ macro has changed subtly over the years,
//       from identifying the GNU C/C++ compiler to identifying any compiler that
//       implements the GNU compiler extensions
#elif defined(__GNUC__)
#   if defined(__GNUC_PATCHLEVEL__)
#       define GNUC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)  // VVRPP
#   else
#       define GNUC_TMP_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)  // VRR00
#   endif
#endif


#endif  // _COMPILER_VERSIONS_H

