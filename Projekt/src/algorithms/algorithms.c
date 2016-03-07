/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include<stdlib.h>
#include "algorithms.h"
#include "mergesort.h"
#include "quicksort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "bubblesort.h"
#include "shellsort.h"
#include "radixsort.h"
#include "stoogesort.h"
#include "oddevensort.h"
#include "heapsort.h"

Algorithm avail[] = {
	{"Merge Sort", &mergesort},
	{"Quick Sort", &quicksort},
	{"Insertion Sort", &insertionsort},
	{"Selection Sort", &selectionsort},
	{"Bubble Sort", &bubblesort},
	{"Shell Sort(Marcin Ciura's gaps + insertion)", &shellsort},
	{"Radix Sort", &radixsort},
	{"Stooge Sort", &stoogesort},
	{"Odd-Even Sort", &oddevensort},
	{"Heap Sort", &heapsort},
	{NULL, NULL},
};

Algorithm *getAvailableAlgorithms(void)
{
	return avail;
}
