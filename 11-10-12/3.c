/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>

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
			}

			length = -1;
		}

		++ length;
	}

	printf("Length Count\n");
	for(int l = 1; l < 81; ++ l)
		if(words[l])
			printf("%5d. %5d\n", l, words[l]); 

	/* 81+ Words */
	if(words[81])
	{
		printf("  81+. %5d\n", words[81]); 
	}

	return 0;
}
