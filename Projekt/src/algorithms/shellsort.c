/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "shellsort.h"
#include "../Event.h"

void shellsort(int *array, const unsigned int size)
{
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	int temp,
		gaps[8] = {701, 301, 132, 57, 23, 10, 4, 1};

	for(unsigned int g = 0; g < 8; ++ g)
		for(unsigned int s = gaps[g]; s < size; ++ s)
			for(unsigned int pos = s; event && pos &&
					(event = raiseEvent(EVENT_TYPE_COMPARE, 2, pos - 1, pos)) &&
					array[pos - 1] > array[pos]; -- pos)
			{
				temp = array[pos];
				array[pos] = array[pos - 1];
				array[pos - 1] = temp;
				event = raiseEvent(EVENT_TYPE_SWAP, 2, pos - 1, pos);
			}

	raiseEvent(EVENT_TYPE_END, 0);
	return;
}
