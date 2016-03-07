/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<limits.h>

int binaryReverse(const int number)
{
	int result = 0;
	for(int b = 0; b < CHAR_BIT * sizeof(int); ++ b)
		result |= (number & (1 << b))?(1 << (CHAR_BIT * sizeof(int) - b - 1)):0;

	return result;
}

int main(void)
{
	int number;
	printf("Give number: ");
	scanf("%d", &number);
	printf("%d\n", binaryReverse(number));

	return 0;
}
