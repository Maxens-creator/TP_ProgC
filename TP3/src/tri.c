#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

int main(void)
{
	int tableau[TAILLE];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < TAILLE; i++) {
		tableau[i] = rand() % 2001 - 1000;
	}

	printf("Tableau non trié :\n");
	for (int i = 0; i < TAILLE; i++) {
		printf("%d%s", tableau[i], i == TAILLE - 1 ? "\n" : " ");
	}

	for (int i = 1; i < TAILLE; i++) {
		int valeur = tableau[i];
		int j = i - 1;

		while (j >= 0 && tableau[j] > valeur) {
			tableau[j + 1] = tableau[j];
			j--;
		}
		tableau[j + 1] = valeur;
	}

	printf("Tableau trié par ordre croissant :\n");
	for (int i = 0; i < TAILLE; i++) {
		printf("%d%s", tableau[i], i == TAILLE - 1 ? "\n" : " ");
	}

	return 0;
}
