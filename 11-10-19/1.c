/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include "1.h"

unsigned long int countSetElements(const ZBIOR set)
{
	unsigned int result = 0;
	for(unsigned int s = 0; s < ROZMIAR; ++ s)
		result += __builtin_popcountl(set[s]);

	return result;
}

void symmetricDifference(const ZBIOR set1, const ZBIOR set2, ZBIOR result)
{
	ZBIOR diff12 = {0},
		  diff21 = {0};

	roznica_z(set1, set2, diff12);
	roznica_z(set2, set1, diff21);
	suma_z(diff12, diff21, result);
}

bool isSubset(const ZBIOR set, const ZBIOR suspect)
{
	for(unsigned int s = 0; s < ROZMIAR; ++ s)
		if((set[s] & suspect[s]) != suspect[s])
			return false;

	return true;
}
