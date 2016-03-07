/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdio.h>
#include "1.h"

void readSet(const char *message, ZBIOR set);

int main(void)
{

	int action;
	ZBIOR set1 = {0},
		  set2 = {0},
		  result = {0};

	printf("Choose action:\n\t1 - Determine number of elements in given set\n\t2 - Compute symmetric difference between two given sets\n\t3 - Decide if given set is subset of another one\n\t0 - Exit\n");
	while(scanf("%d", &action) != -1 && action)
	{
		switch(action)
		{
			case 1:
				puts("##### Determine number of elements in given set #####");
				readSet("Give set:", set1);
				printf("Given set has %lu elements\n", countSetElements(set1));
				break;

			case 2:
				puts("##### Compute symmetric difference #####");
				readSet("Give set A:", set1);
				readSet("Give set B:", set2);
				symmetricDifference(set1, set2, result);
				for(ELEMENT e = 0; e < MAX_ELEM; ++ e)
					if(element_z(e, result))
						printf("%lu ", e);

				puts("");
				break;

			case 3:
				puts("##### Decide if given set is subset of another one #####");
				readSet("Give set A:", set1);
				readSet("Give set B:", set2);
				printf("B is %sa subset of A\n", isSubset(set1, set2)?"":"not ");
				break;

			default:
				puts("Invalid action!");
				break;
		}

		printf("Chose action: ");
	}

	puts("Bye!");
	return 0;
}

void readSet(const char *message, ZBIOR set)
{
	long int number;
	wyczysc_z(set);
	puts(message);
	printf("* -1 as end of set\n");
	while(scanf("%ld", &number) != -1 && number != -1)
		dodaj_e(number, set);

	return;

}
