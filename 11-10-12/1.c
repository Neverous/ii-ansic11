/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include<stdbool.h>

int main(void)
{
	int act,
		lastCharacter = '\n';
	bool spaceLast = false;
	while((act = getchar()) != EOF)
	{
		if(act == ' ')
			spaceLast = true;

		else
		{
			if(lastCharacter != '\n' && act != '\n' && spaceLast)
				putchar(' ');

			spaceLast = false;
			putchar(act);
			lastCharacter = act;
		}
	}

	return 0;
}
