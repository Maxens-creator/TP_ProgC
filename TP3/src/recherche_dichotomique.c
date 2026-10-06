#include <stdio.h>

#define TAILLE 100

int main(void)
{
	int tableau[TAILLE];
	int recherche;
	int gauche = 0;
	int droite = TAILLE - 1;
	int trouve = 0;

	for (int i = 0; i < TAILLE; i++) {
		tableau[i] = i - 50;
	}

	printf("Tableau trié :\n");
	for (int i = 0; i < TAILLE; i++) {
		printf("%d%s", tableau[i], i == TAILLE - 1 ? "\n" : " ");
	}

	printf("Entrez l'entier que vous souhaitez chercher : ");
	fflush(stdout);
	if (scanf("%d", &recherche) != 1) {
		fprintf(stderr, "Entrée invalide.\n");
		return 1;
	}

	while (gauche <= droite) {
		int milieu = gauche + (droite - gauche) / 2;

		if (tableau[milieu] == recherche) {
			trouve = 1;
			break;
		}
		if (tableau[milieu] < recherche) {
			gauche = milieu + 1;
		} else {
			droite = milieu - 1;
		}
	}

	if (trouve) {
		printf("Résultat : entier présent\n");
	} else {
		printf("Résultat : entier absent\n");
	}

	return 0;
}
