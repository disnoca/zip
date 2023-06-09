#ifndef _CONCURRENCY_H
#define _CONCURRENCY_H

#define MIN(a,b) (((a)<(b))?(a):(b))

#define MIN_SIZE_FOR_CONCURRENCY 1048576	// 1 MB

/**
 * Returns the number of cores in the system.
 * 
 * @return the number of cores in the system
*/
unsigned num_cores();

#endif