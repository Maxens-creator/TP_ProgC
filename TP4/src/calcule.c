#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "operator.h"

static int convertir_entier(const char *texte, int *valeur)
{
	char *fin_lecture;
	errno = 0;
	long valeur_longue = strtol(texte, &fin_lecture, 10);
	if (errno == ERANGE || fin_lecture == texte || *fin_lecture != '\0'
		|| valeur_longue < INT_MIN || valeur_longue > INT_MAX) {
		return 0;
	}

	*valeur = (int)valeur_longue;
	return 1;
}

int main(int argc, char *argv[])
{
	int num1;
	int num2;
	int resultat;

	if (argc != 4 || argv[1][0] == '\0' || argv[1][1] != '\0'
		|| !convertir_entier(argv[2], &num1)
		|| !convertir_entier(argv[3], &num2)) {
		fprintf(stderr, "Usage : %s <opérateur> <num1> <num2>\n", argv[0]);
		return 1;
	}

	if (!executer_operation(num1, num2, argv[1][0], &resultat)) {
		fprintf(stderr, "Opération inconnue ou division impossible.\n");
		return 1;
	}

	printf("Résultat : %d\n", resultat);
	return 0;
}
