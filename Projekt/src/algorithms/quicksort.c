/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "quicksort.h"
#include "../Event.h"

void QuickSort(int *array, int start, int end)
{
	if(start >= end)
		return;

	int middle = (start + end) / 2,
		i = start, j = end - 1,
		temp = 0;
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	if(!event)
		return;

	if((event = raiseEvent(EVENT_TYPE_SWAP, 2, middle, end)))
	{
		temp = array[middle];
		array[middle] = array[end];
		array[end] = temp;
		event = raiseEvent(EVENT_TYPE_SWAP, 2, middle, end);
	}

	for(i = start; event && i < j;)
	{
		if((event = raiseEvent(EVENT_TYPE_COMPARE, 2, i, end)) && 
		   array[i] >= array[end] && (event = raiseEvent(EVENT_TYPE_SWAP, 2, i, j)))
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			event = raiseEvent(EVENT_TYPE_SWAP, 2, i, j);
			-- j;
		}

		else
			++ i;
	}

	if(array[j] < array[end])
		++ j;

	if((event = raiseEvent(EVENT_TYPE_SWAP, 2, j, end)))
	{
		temp = array[j];
		array[j] = array[end];
		array[end] = temp;
		event = raiseEvent(EVENT_TYPE_SWAP, 2, j, end);
	}

	if(event)
	{
		QuickSort(array, start, j - 1);
		QuickSort(array, j + 1, end);
	}
}

void quicksort(int *array, const unsigned int size)
{
	QuickSort(array, 0, size - 1);
	raiseEvent(EVENT_TYPE_END, 0);
}
