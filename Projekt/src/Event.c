/* 2012
 * Maciej Szeptuch
 * II UWr
 */
#define _POSIX_C_SOURCE 199309L //Needed for nanosleep
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "Event.h"
#include "GUI.h"

bool raiseEvent(EventType type, const unsigned int arguments, ...)
{
	AppState *state = getAppState();
	if(!state->running)
		return false;

	if(type == EVENT_TYPE_CHECK)
		return state->running;

	va_list arg; // List of function arguments
	static int args[256]; // event arguments
	static int prevArguments = 0;
	for(int a = 0; a < prevArguments; ++ a) // reset previous event colors
		drawColumn(args[a], 0xFFFFFF, state);

	prevArguments = arguments;
	va_start(arg, arguments);
	for(unsigned int a = 0; a < arguments; ++ a)
		args[a] = va_arg(arg, int);

	va_end(arg);
	switch(type)
	{
		case EVENT_TYPE_COMPARE:
			drawColumn(args[0], 0xFF0000, state);
			drawColumn(args[1], 0xFF0000, state);
			break;

		case EVENT_TYPE_SWAP:
			drawColumn(args[0], 0x00FF00, state);
			drawColumn(args[1], 0x00FF00, state);
			break;

		case EVENT_TYPE_END:
		case EVENT_TYPE_CHECK:
			for(int s = 0; s < state->arraySize; ++ s)
				drawColumn(s, 0xFFFFFF, state);

			return false;
	}

	struct timespec sec = {0, 500000}; // 0.0005s
	nanosleep(&sec, NULL);
	return true;
}
