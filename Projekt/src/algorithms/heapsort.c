/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#include "heapsort.h"
#include "../Event.h"

bool sift(int *array, int start, int count)
{
	int root = start,
		child = 0,
		temp = 0;
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);
	while(event && root * 2 + 1 < count)
	{
		child = root * 2 + 1;
		if(child + 1 < count && (event = raiseEvent(EVENT_TYPE_COMPARE, 2,
													child, child + 1)) &&
		   array[child] < array[child + 1])
			++ child;

		if(event && (event = raiseEvent(EVENT_TYPE_COMPARE, 2, root, child)) &&
		   array[root] < array[child] && (event = raiseEvent(EVENT_TYPE_SWAP, 2,
				   											 root, child)))
		{
			temp = array[root];
			array[root] = array[child];
			array[child] = temp;
			event = raiseEvent(EVENT_TYPE_SWAP, 2, root, child);
			root = child;
		}

		else
			return event;
	}

	return event;
}

void heapsort(int *array, const unsigned int size)
{
	int start = size / 2 - 1,
		end = size - 1,
		temp = 0;
	bool event = raiseEvent(EVENT_TYPE_CHECK, 0);

	while(event && start >= 0)
		event = sift(array, start --, size);

	while(event && end > 0 && (event = raiseEvent(EVENT_TYPE_SWAP, 2, 0, end)))
	{
		temp = array[0];
		array[0] = array[end];
		array[end] = temp;
		event = raiseEvent(EVENT_TYPE_SWAP, 2, 0, end);
		sift(array, 0, end --);
	}

	raiseEvent(EVENT_TYPE_END, 0);
	return;
}
