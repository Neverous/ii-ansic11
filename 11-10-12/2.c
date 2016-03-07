/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>

int decode(int character);

int main(void)
{
	int act,
		lastCharacter = '\n';
	while((act = getchar()) != EOF)
	{
		act = decode(act);
		if(act != '\n')
				putchar(act);

		else if(lastCharacter != '\n')
			putchar(act);

		lastCharacter = act;
	}

	return 0;
}

int decode(int character)
{
	if(character == ' ' || character == '\n' || character == '\t')
		return '\n';

	if(character >= 'A' && character <= 'Z')
		character -= 'A' - 'a';

	return character;
}
