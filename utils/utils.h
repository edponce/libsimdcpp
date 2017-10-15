#ifndef _UTILS_H
#define _UTILS_H


/*!
 *  Configure OpenMP environment
 */
int setOmpEnv(const int);

/*!
 *  Detect CPU SIMD features
 */
int detectProcSIMD();
int detectIntelProcSIMD();

/*!
 *  Print some system configurations
 */
void printSysconf();

/*!
 *  Get the number of processors currently online (available)
 */
long int getNumProcOnline();

/*!
 *  Get the size of page in bytes
 */
long int getPageSz();

/*!
 *  Get the size in bytes of L1 data cache
 */
long int getL1Sz();

/*!
 *  Get the line size in bytes of L1 data cache
 */
long int getL1LineSz();

/*!
 *  Get the associativity of L1 data cache
 */
long int getL1Assoc();

/*!
 *  Get the size in bytes of L2 cache
 */
long int getL2Sz();

/*!
 *  Get the line size in bytes of L2 cache
 */
long int getL2LineSz();

/*!
 *  Get the associativity of L2 cache
 */
long int getL2Assoc();

/*!
 *  Get the size in bytes of L3 cache
 */
long int getL3Sz();

/*!
 *  Get the line size in bytes of L3 cache
 */
long int getL3LineSz();

/*!
 *  Get the associativity of L3 cache
 */
long int getL3Assoc();


#endif  // _UTILS_H

