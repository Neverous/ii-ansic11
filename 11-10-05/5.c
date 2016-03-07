/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#define M_PI 3.14

long double sin(long double number);
long double cos(long double number);
long double degToRad(int deg);

int main(void)
{
	puts("Number |  Sin  |  Cos");
	for(int n = 0; n <= 180; ++ n)
		printf(" %5d | %3.2Lf | %3.2Lf\n", n, sin(degToRad(n)), cos(degToRad(n)));

	return 0;
}

long double sin(long double number)
{
	long double result = number,
				up = number * number * number,
				down = 6;

	for(int i = 0; i < 7; ++ i)
	{
		result += ((i % 2)?1:-1) * up / down;
		up *= number * number;
		down *= (2 * i + 4) * (2 * i + 5);
	}

	return result;
}

long double cos(long double number)
{
	long double result = 1,
				up = number * number,
				down = 2;

	for(int i = 0; i < 7; ++ i)
	{
		result += ((i % 2)?1:-1) * up / down;
		up *= number * number;
		down *= (2 * i + 3) * (2 * i + 4);
	}

	return result;
}

long double degToRad(int deg)
{
	return M_PI * deg / 180.0;
}
