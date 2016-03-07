/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<stdbool.h>

inline static const bool isEqualWithShift(const char *first, const char *second, const int shift, const int size);
inline static const int findCookies(FILE *file);

int main(int argc, char *argv[])
{
	FILE *file;
	if(argc < 2)
	{
		printf("Usage: %s file1 file2 ...\n", argv[0]);
		return  1;
	}

	for(int i = 1; i < argc; ++ i)
	{
		file = fopen(argv[i], "r");
		if(file == NULL)
		{
			printf("could not open %s\n", argv[i]);
			continue;
		}

		printf("found %d cookies in %s\n", findCookies(file), argv[i]);
		fclose(file);
	}

	return 0;
}

inline static const int findCookies(FILE *file)
{
	char data[6];
	int count = 0;
	for(int c = 0, act = 0; (act = fgetc(file)) != -1; ++ c)
	{
		data[c % 6] = act;
		if(c >= 5 && isEqualWithShift(data, "cookie", (c - 5) % 6, 6))
			++ count;
	}

	return count;
}

inline static const bool isEqualWithShift(const char *first, const char *second, const int shift, const int size)
{
	for(int s = 0; s < size; ++ s)
		if(first[(shift + s) % size] != second[s])
			return false;

	return true;
}
