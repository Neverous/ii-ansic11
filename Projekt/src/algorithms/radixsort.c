/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "radixsort.h"
#include "../Event.h"

int digit(int number, const int dig)
{
	for(int d = 0; d < dig; ++ d)
		number /= 10;

	return number % 10;
}

void radixsort(int *array, const unsigned int size)
{
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	int helper[10][1024];
	for(int d = 0; event && d < 4; ++ d)
	{
		for(int i = 0; (event = raiseEvent(EVENT_TYPE_CHECK, 0)) && i < 10; 
			++ i)
			helper[i][0] = 0;

		for(unsigned int s = 0; (event = raiseEvent(EVENT_TYPE_CHECK, 0)) &&
			s < size; ++ s)
			helper[digit(array[s], d)][++ helper[digit(array[s], d)][0]] =
				array[s];

		for(int i = 0, s = 0; event && i < 10; ++ i)
			for(int h = 1; event && (event = raiseEvent(EVENT_TYPE_SWAP, 2, s,
														s)) && 
				h <= helper[i][0]; ++ h)
			{
				array[s ++] = helper[i][h];
				event = raiseEvent(EVENT_TYPE_SWAP, 2, s, s);
			}
	}

	raiseEvent(EVENT_TYPE_END, 0);
	return;
}
