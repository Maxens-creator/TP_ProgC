#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int tableau[100];
	int plus_grand;
	int plus_petit;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 100; i++) {
		tableau[i] = rand() % 1000 + 1;
	}

	plus_grand = tableau[0];
	plus_petit = tableau[0];

	for (int i = 1; i < 100; i++) {
		if (tableau[i] > plus_grand) {
			plus_grand = tableau[i];
		}
		if (tableau[i] < plus_petit) {
			plus_petit = tableau[i];
		}
	}

	printf("Le numéro le plus grand est : %d\n", plus_grand);
	printf("Le numéro le plus petit est : %d\n", plus_petit);

	return 0;
}
