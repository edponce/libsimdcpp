#ifndef _TEST_UTILS_H
#define _TEST_UTILS_H


enum TEST_TYPES { TEST_U16, TEST_U32, TEST_U64,   // unsigned
                  TEST_I16, TEST_I32, TEST_I64,   // signed
                  TEST_FLT, TEST_DBL }; // floating-point


void create_test_array(const int, void ** const, const int, const int);
int validate_test_arrays(const int, const void * const, const void * const, const int);


#endif  // _TEST_UTILS_H

