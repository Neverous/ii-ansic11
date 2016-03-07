/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>

unsigned int size;
long double seq[1048576];

inline static void merge(long double *start, long double *middle, long double *end);
inline static void mergeSort(long double *start, long double *end);

int main(void)
{
	printf("List size: ");
	scanf("%u", &size);

	printf("Elements: ");
	for(unsigned int s = 0; s < size; ++ s)
		scanf("%Lf", &seq[s]);

	mergeSort(seq, seq + size);
	puts("Result: ");
	for(unsigned int s = 0; s < size; ++ s)
		printf("%.2Lf ", seq[s]);

	puts("");
	return 0;
}

inline static void merge(long double *start, long double *middle, long double *end)
{
	long double temp[end - start];
	long double *f = start,
				*s = middle;

	for(unsigned int t = 0; f != middle || s != end; ++ t)
	{
		if(s == end || (f != middle && *f < *s))
			temp[t] = *(f ++);

		else
			temp[t] = *(s ++);
	}

	f = start;
	for(unsigned int t = 0, e = end - start; t < e; ++ t, ++ f)
		*f = temp[t];

	return;
}

inline static void mergeSort(long double *start, long double *end)
{
	long double temp,
				*middle;
	if(end - start == 1)
		return;

	if(end - start == 2)
	{
		if(*start > *(start + 1))
		{
			temp = *start;
			*start = *(start + 1);
			*(start + 1) = temp;
		}

		return;
	}

	middle = start + (end - start + 1) / 2;
	mergeSort(start, middle);
	mergeSort(middle, end);
	merge(start, middle, end);
	return;
}
