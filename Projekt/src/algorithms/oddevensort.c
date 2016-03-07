/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "oddevensort.h"
#include "../Event.h"

void oddevensort(int *array, const unsigned int size)
{
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0),
		 swapped = true;
	int temp;
	while(event && swapped)
	{
		swapped = false;
		for(unsigned int s = 1; event && s < size; s += 2)
		{
			if((event = raiseEvent(EVENT_TYPE_COMPARE, 2, s - 1, s)) &&
			   array[s] < array[s - 1] && (event = raiseEvent(EVENT_TYPE_SWAP,
					   										   2, s - 1, s)))
			{
				swapped = true;
				temp = array[s - 1];
				array[s - 1] = array[s];
				array[s] = temp;
				event = raiseEvent(EVENT_TYPE_SWAP, 2, s - 1, s);
			}
		}

		swapped = false;
		for(unsigned int s = 2; event && s < size; s += 2)
		{
			if((event = raiseEvent(EVENT_TYPE_COMPARE, 2, s - 1, s)) &&
			   array[s] < array[s - 1] && (event = raiseEvent(EVENT_TYPE_SWAP,
					   										   2, s - 1, s)))
			{
				swapped = true;
				temp = array[s - 1];
				array[s - 1] = array[s];
				array[s] = temp;
				event = raiseEvent(EVENT_TYPE_SWAP, 2, s - 1, s);
			}
		}
	}

	raiseEvent(EVENT_TYPE_END, 0);
	return;
}
