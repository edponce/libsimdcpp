#ifndef _TEST_UTILS_H
#define _TEST_UTILS_H


#include <stdlib.h>  // free, NULL
/*!
 *  \brief Deallocate dynamic memory and nullify pointer
 */
#define FREE(p) free(p); p = NULL


enum TEST_TYPES { TEST_U8, TEST_U16, TEST_U32, TEST_U64,  // unsigned integers
                  TEST_I8, TEST_I16, TEST_I32, TEST_I64,  // signed integers
                  TEST_FLT, TEST_DBL };          // floating-point numbers


void create_test_array(const int32_t, void ** const, const int32_t, const int32_t);
int32_t validate_test_arrays(const int32_t, const void * const, const void * const, const int32_t);


#endif  // _TEST_UTILS_H

