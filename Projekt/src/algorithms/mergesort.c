/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "mergesort.h"
#include "../Event.h"

void MergeSort(int *array, int start, int end)
{
	if(start == end)
		return;

	int middle = (start + end) / 2,
		helper[end - start + 1],
		i = 0, j = 0,
		place = 0;
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	if(!event)
		return;

	MergeSort(array, start, middle);
	MergeSort(array, middle + 1, end);
	for(i = start, j = middle + 1, place = 0; event && (i <= middle || j <= end);)
	{
		if(j > end || (i <= middle && (event = raiseEvent(EVENT_TYPE_COMPARE, 2, i, j)) && array[i] < array[j]))
			helper[place ++] = array[i ++];

		else if(event && (i > middle || (j <= end && (event = raiseEvent(EVENT_TYPE_COMPARE, 2, i, j)) && array[i] >= array[j])))
			helper[place ++] = array[j ++];
	}

	for(i = start; event && i <= end; ++ i)
		if((event = raiseEvent(EVENT_TYPE_SWAP, 2, i, i)))
		{
			array[i] = helper[i - start];
			event = raiseEvent(EVENT_TYPE_SWAP, 2, i, i);
		}

	return;
}

void mergesort(int *array, const unsigned int size)
{
	MergeSort(array, 0, size - 1);
	raiseEvent(EVENT_TYPE_END, 0);
}
