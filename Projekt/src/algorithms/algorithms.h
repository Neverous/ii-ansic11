/* 2012
 * Maciej Szeptuch
 * II UWr
 * ----------
 *  Allows to keep track of available algorithms.
 */
#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

typedef struct
{
	const char *name;
	void (*function)(int *, const unsigned int);
} Algorithm;

/*
 * Function that returns available algorithms.
 */
Algorithm *getAvailableAlgorithms(void);
#endif
