/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<stdbool.h>

inline static const char lower(const char c);
inline static const bool isEqualWithShiftAndLower(const char *first, const char *second, const int shift, const int size, const int count); // with lower!
inline static void eatCookiesAndBiscuits(FILE *input, FILE *output);

int main(int argc, char *argv[])
{
	FILE *input,
		 *output;
	if(argc < 3)
	{
		printf("Usage: %s input output\n", argv[0]);
		return  1;
	}

	input = fopen(argv[1], "r");
	if(input == NULL)
	{
		printf("could not open %s\n", argv[1]);
		return 1;
	}

	output = fopen(argv[2], "w");
	if(output == NULL)
	{
		printf("could not open %s\n", argv[2]);
		return 1;
	}

	eatCookiesAndBiscuits(input, output);
	fclose(input);
	fclose(output);

	return 0;
}

inline static const char lower(const char c)
{
	if(c >= 'A' && c <= 'Z')
		return c - 'A' + 'a';

	return c;
}

inline static const bool isEqualWithShiftAndLower(const char *first, const char *second, const int shift, const int size, const int count)
{
	for(int s = 0; s < count; ++ s)
		if(lower(first[(shift + s) % size]) != second[s])
			return false;

	return true;
}

inline static void eatCookiesAndBiscuits(FILE *input, FILE *output)
{
	char data[7];
	int c, act, notprint;
	for(c = 0, act = 0, notprint = 0; (act = fgetc(input)) != -1; ++ c, -- notprint)
	{
		data[c % 7] = act;
		if(notprint > 0)
			continue;

		if(c > 4 && isEqualWithShiftAndLower(data, "cookie", (c - 5) % 7, 7, 6))
			notprint = 7;

		if(c < 6)
			continue;

		if(isEqualWithShiftAndLower(data, "biscuit", (c - 6) % 7, 7, 7))
			notprint = 7;

		else
			fputc(data[(c - 6) % 7], output);
	}

	if(notprint <= 0)
		for(int s = 0; s < 6; ++ s)
			fputc(data[(c - 6 + s) % 7], output);

	return;
}
