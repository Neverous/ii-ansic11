/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>

const int DIAGRAM_LENGTH = 50;

void printStars(int counter);

int main(void)
{
	int length = 0,
		act,
		words[128] = {0};
	while((act = getchar()) != EOF)
	{
		if(act == ' ' || act == '\n' || act == '\t')
		{
			if(length)
			{
				if(length > 80)
					length = 81;

				++ words[length];
				++ words[0];
			}

			length = -1;
		}

		++ length;
	}

	printf("Length Count | Percent | Diagram\n");
	for(int l = 1; l < 81; ++ l)
		if(words[l])
		{
			printf("%5d. %5d | %6.3Lf%% | ", l, words[l], (long double)words[l] / words[0] * 100); 
			printStars(DIAGRAM_LENGTH * words[l] / words[0]);
			puts("");
		}

	/* 81+ Words */
	if(words[81])
	{
		printf("  81+. %5d | %6.3Lf%% | ", words[81], (long double)words[81] / words[0] * 100); 
		printStars(DIAGRAM_LENGTH * words[81] / words[0]);
		puts("");
	}

	return 0;
}

void printStars(int counter)
{
	for(int c = 0; c < counter; ++ c)
		putchar('*');

	return;
}
