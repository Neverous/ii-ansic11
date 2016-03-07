/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define MAXDEGREE 10

void sum(long double *firstPoly, long double *secondPoly, long double *resultPoly);
void prod(long double *firstPoly, long double *secondPoly, long double *resultPoly, unsigned int *overflow);

int main(void)
{
	long double first[MAXDEGREE] = {0},
				second[MAXDEGREE] = {0},
				result[MAXDEGREE] = {0};
	unsigned int overflow = 0;

	printf("Write first polynomial: ");
	for(int p = 0; p < MAXDEGREE; ++ p)
	{
		printf("x^%d: ", p);
		scanf("%Lf", &first[p]);
	}

	printf("Write second polynomial: ");
	for(int p = 0; p < MAXDEGREE; ++ p)
	{
		printf("x^%d: ", p);
		scanf("%Lf", &second[p]);
	}

	puts("");
	sum(first, second, result);
	printf("Sum of given polynomials: ");
	for(int p = 0; p < MAXDEGREE; ++ p)
		printf("%Lfx^%d%s", result[p], p, p < MAXDEGREE - 1?" + ":"\n"); 

	prod(first, second, result, &overflow);
	printf("Product of given polynomials(overflow = %d): ", overflow);
	for(int p = 0; p < MAXDEGREE; ++ p)
		printf("%Lfx^%d%s", result[p], p, p < MAXDEGREE - 1?" + ":"\n"); 

	return 0;
}

void sum(long double *firstPoly, long double *secondPoly, long double *resultPoly)
{
	for(int r = 0; r < MAXDEGREE; resultPoly[r ++] = 0);

	for(int p = 0; p < MAXDEGREE; ++ p)
		resultPoly[p] = firstPoly[p] + secondPoly[p];

	return;
}

void prod(long double *firstPoly, long double *secondPoly, long double *resultPoly, unsigned int *overflow)
{
	bool error = false;
	for(int r = 0; r < MAXDEGREE; resultPoly[r ++] = 0);

	for(int f = 0; f < MAXDEGREE; ++ f)
		for(int s = 0; firstPoly[f] && s < MAXDEGREE; ++ s)
		{
			if(!secondPoly[s])
				continue;

			if(f + s >= MAXDEGREE)
			{
				error = true;
				break;
			}

			resultPoly[f + s] += firstPoly[f] * secondPoly[s];
		}

	*overflow += error;
}
