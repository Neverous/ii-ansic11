/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool isPrime(int number);

int main(void)
{
	int number;
	printf("Number to check: ");
	scanf("%d", &number);

	printf("%d is %sa prime number\n", number, isPrime(number)?"":"not ");
	return 0;
}

bool isPrime(int number)
{
	for(int n = 2; n * n <= number; ++ n)
		if(number % n == 0)
			return false;

	return true;
}
