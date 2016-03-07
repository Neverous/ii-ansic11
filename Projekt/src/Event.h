/* 2012
 * Maciej Szeptuch
 * II UWr
 * ----------
 *  Very simple event interface.
 */
#ifndef __EVENT_H
#define __EVENT_H
#include<stdarg.h>
#include<stdbool.h>

/*
 * POSSIBLE EVENTS
 * 	- COMPARE - comparison of two elements. Two arguments - compared positions
 * 				in array.
 * 	- SWAP - swap of two elements. Two arguments - swapped positions in array.
 * 	- CHECK - check if may work.
 * 	- END - the algorithm has ended.
 */
#define EVENT_TYPES 4
typedef enum
{
	EVENT_TYPE_COMPARE,
	EVENT_TYPE_SWAP,
	EVENT_TYPE_CHECK,
	EVENT_TYPE_END,
} EventType;

/*
 * Function that handles the event.
 * 	First argument is the event type, second is number of arguments passed and 
 * 	next are those arguments.
 *	Returns false if function that "raised" event should immediately stop, true
 *	otherwise.
 */
bool raiseEvent(EventType type, const unsigned int arguments, ...);
#endif
