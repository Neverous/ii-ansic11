/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdbool.h>
#include "zbiory.h"

/* Function that counts number of elements in given set */
unsigned long int countSetElements(const ZBIOR set);

/* Function that computes symmetric difference between set1 and set2 */
void symmetricDifference(const ZBIOR set1, const ZBIOR set2, ZBIOR result);

/* Function that decides whether a suspect is subset of set */
bool isSubset(const ZBIOR set, const ZBIOR suspect);
