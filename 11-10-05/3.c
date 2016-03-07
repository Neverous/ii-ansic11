/* 2011
 * Maciej Szeptuch
 * II UWr
 */
#include<stdlib.h>
#include<stdio.h>

int main(void)
{
	printf("%u %u\n", sizeof(long double), sizeof(double));
	long double money,
				desiredMoney;
	int rate,
		years = 0;
	printf("Starting money: ");
	scanf("%Lf", &money);

	printf("Interest rate(0-100): ");
	scanf("%d", &rate);

	printf("Desired money: ");
	scanf("%Lf", &desiredMoney);

	while(money < desiredMoney)
	{
		years ++;
		money *= (100.0 + rate) / 100.0;
		printf("%d %11.2Lf\n", years, money);
	}

	printf("You need %d years to reach desired amount of money.\n", years);
	return 0;
}
