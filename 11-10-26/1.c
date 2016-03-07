/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>

const char HEXDIGIT[32] = "0123456789ABCDEF";

unsigned int number;

void printhex(unsigned int x);
void printbin(unsigned int x);

int main(void)
{
	printf("Number: ");
	scanf("%u", &number);
	printf("Hexadecimal representation: ");
	printhex(number);
	puts("");

	printf("Binary representation: ");
	printbin(number);
	puts("");
	return 0;
}

void printhex(unsigned int x)
{
	char result[16] = {0};
	int r = 0;

	do
	{
		result[r ++] = x % 16;
		x /= 16;
	}
	while(x);

	while(r > 0)
		putchar(HEXDIGIT[(int) result[-- r]]);

	return;
}

void printbin(unsigned int x)
{
	char result[64] = {0};
	int r = 0;

	do
	{
		result[r ++] = x % 2;
		x /= 2;
	}
	while(x);

	while(r > 0)
		putchar(result[-- r] + '0');

	return;
}
