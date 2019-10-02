#ifndef _VUTILS_H
#define _VUTILS_H


#include "simd.h"
#if defined(SIMD_MODE)


int scalar_malloc(int ** const, const size_t, const size_t);
int scalar_malloc(unsigned int ** const, const size_t, const size_t);
int scalar_malloc(long int ** const, const size_t, const size_t);
int scalar_malloc(unsigned long int ** const, const size_t, const size_t);
int scalar_malloc(float ** const, const size_t, const size_t);
int scalar_malloc(double ** const, const size_t, const size_t);
void scalar_free(int ** const);
void scalar_free(unsigned int ** const);
void scalar_free(long int ** const);
void scalar_free(unsigned long int ** const);
void scalar_free(float ** const);
void scalar_free(double ** const);
int simd_malloc(SIMD_INT ** const, const size_t, const size_t);
int simd_malloc(SIMD_FLT ** const, const size_t, const size_t);
int simd_malloc(SIMD_DBL ** const, const size_t, const size_t);
void simd_free(SIMD_INT ** const);
void simd_free(SIMD_FLT ** const);
void simd_free(SIMD_DBL ** const);
void simd_print(const char * const, const SIMD_INT);
void simd_print(const char * const, const SIMD_FLT);
void simd_print(const char * const, const SIMD_DBL);


#endif // SIMD_MODE


#endif  // _VUTILS_H
