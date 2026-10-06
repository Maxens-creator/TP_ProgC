#include <stdio.h>

#include "fichier.h"

int lire_fichier(const char *nom_de_fichier)
{
	FILE *flux = fopen(nom_de_fichier, "r");
	if (flux == NULL) {
		perror(nom_de_fichier);
		return 0;
	}

	printf("Contenu du fichier %s :\n", nom_de_fichier);
	int caractere;
	while ((caractere = fgetc(flux)) != EOF) {
		if (fputc(caractere, stdout) == EOF) {
			fclose(flux);
			fprintf(stderr, "Erreur lors de l'affichage du fichier.\n");
			return 0;
		}
	}

	int erreur = ferror(flux);
	if (fclose(flux) != 0) {
		erreur = 1;
	}
	if (erreur) {
		perror(nom_de_fichier);
		return 0;
	}

	return 1;
}

int ecrire_dans_fichier(const char *nom_de_fichier, const char *message)
{
	FILE *flux = fopen(nom_de_fichier, "w");
	if (flux == NULL) {
		perror(nom_de_fichier);
		return 0;
	}

	int erreur = fprintf(flux, "%s\n", message) < 0;
	if (fclose(flux) != 0) {
		erreur = 1;
	}
	if (erreur) {
		perror(nom_de_fichier);
		return 0;
	}

	printf("Le message a été écrit dans le fichier %s.\n", nom_de_fichier);
	return 1;
}
