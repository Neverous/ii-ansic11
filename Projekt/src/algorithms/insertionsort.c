/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "insertionsort.h"
#include "../Event.h"

void insertionsort(int *array, const unsigned int size)
{
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	int temp;
	for(unsigned int s = 0; event && s < size; ++ s)
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
