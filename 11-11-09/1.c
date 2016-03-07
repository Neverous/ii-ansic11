/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>

unsigned int size,
			 seq[1048576],
			 value;
const unsigned int *res;

const unsigned int *find(const unsigned int val, const unsigned int *start, const unsigned int *end);

int main(void)
{
	printf("List length: ");
	scanf("%u", &size);
	
	printf("Elements: ");
	for(unsigned int s = 0; s < size; ++ s)
		scanf("%u", &seq[s]);

	printf("Value to find: ");
	scanf("%u", &value);

	
	res = find(value, seq, seq + size);
	puts("");
	puts(res?"Element found!":"Element not found!");
	return 0;
}
/*
unsigned int *find(const unsigned int val, const unsigned int *start, const unsigned int *end)
{
	for(unsigned int *act = start; act != end; ++ act)
		if(val == *act)
			return act;
	
	return NULL;
}
*/
/* FAST FIND */
const unsigned int *find(const unsigned int val, const unsigned int *start, const unsigned int *end)
{
	if(start + 1 == end)
	{
		if(*start == value)
			return start;

		return NULL;
	}

	if(*(start + (end - start + 1) / 2) > value)
		return find(val, start, start + (end - start + 1) / 2);

	return find(val, start + (end - start + 1) / 2, end);
}
