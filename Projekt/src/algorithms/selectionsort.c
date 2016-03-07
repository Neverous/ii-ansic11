/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "selectionsort.h"
#include "../Event.h"

void selectionsort(int *array, const unsigned int size)
{
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	int temp;
	for(unsigned int s = 0, min = 0; event && s < size; min = ++ s)
	{
		for(unsigned int pos = s; event && pos < size; ++ pos)
		{
			event = raiseEvent(EVENT_TYPE_COMPARE, 2, min, pos);
			if(array[min] > array[pos])
				min = pos;

		}

		if((event = raiseEvent(EVENT_TYPE_SWAP, 2, s, min)))
		{
			temp = array[min];
			array[min] = array[s];
			array[s] = temp;
			event = raiseEvent(EVENT_TYPE_COMPARE, 2, s, min);
		}
	}

	raiseEvent(EVENT_TYPE_END, 0);
	return;
}
