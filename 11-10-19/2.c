/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<limits.h>

unsigned int countOnes(int number);

int main(void)
{
	int number;
	printf("Give number to check: ");
	scanf("%d", &number);
	printf("%u[builtin: %u]\n", countOnes(number), __builtin_popcount(number));
	/* x & (x - 1) removes one of ones in binary representation */
	return 0;
}

unsigned int countOnes(int number)
{
	int ones = 0;
	for(int p = 0; p < sizeof(int) * CHAR_BIT; ++ p)
		ones += ((1 << p) & number) != 0;

	return ones;
}
