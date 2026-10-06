#include <stdio.h>

#include "operator.h"

static int exercice_4_1(void)
{
	int num1;
	int num2;
	int resultat;
	char operateur;

	printf("Entrez num1 : ");
	if (scanf("%d", &num1) != 1) {
		fprintf(stderr, "Entrée invalide.\n");
		return 1;
	}
	printf("Entrez num2 : ");
	if (scanf("%d", &num2) != 1) {
		fprintf(stderr, "Entrée invalide.\n");
		return 1;
	}
	printf("Entrez l'opérateur (+, -, *, /, %%, &, |, ~) : ");
	if (scanf(" %c", &operateur) != 1) {
		fprintf(stderr, "Opérateur invalide.\n");
		return 1;
	}

	if (!executer_operation(num1, num2, operateur, &resultat)) {
		fprintf(stderr, "Opération invalide ou division impossible.\n");
		return 1;
	}

	printf("Résultat : %d\n", resultat);
	return 0;
}

int main(void)
{
	int choix;

	printf("Choisissez l'exercice :\n");
	printf("1. Calcul avec opérateurs\n");
	printf("Votre choix : ");
	if (scanf("%d", &choix) != 1) {
		fprintf(stderr, "Choix invalide.\n");
		return 1;
	}

	switch (choix) {
	case 1:
		return exercice_4_1();
	default:
		fprintf(stderr, "Exercice invalide.\n");
		return 1;
	}
}

