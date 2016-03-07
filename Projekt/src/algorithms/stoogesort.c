/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "stoogesort.h"
#include "../Event.h"

void StoogeSort(int *array, int start, int end)
{
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	if(!event)
		return;

	int temp;
	if((event = raiseEvent(EVENT_TYPE_COMPARE, 2, start, end)) &&
		array[start] > array[end] && (event = raiseEvent(EVENT_TYPE_SWAP, 2,
														 start, end)))
	{
		temp = array[end];
		array[end] = array[start];
		array[start] = temp;
		event = raiseEvent(EVENT_TYPE_SWAP, 2, start, end);
	}

	if(event && end - start + 1 >= 3)
	{
		temp = (end - start + 1) / 3;
		StoogeSort(array, start, end - temp);
		StoogeSort(array, start + temp, end);
		StoogeSort(array, start, end - temp);
	}

	return;
}

void stoogesort(int *array, const unsigned int size)
{
	StoogeSort(array, 0, size - 1);
	raiseEvent(EVENT_TYPE_END, 0);
}
