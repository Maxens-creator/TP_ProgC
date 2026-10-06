#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define TAILLE_NOM_FICHIER 256
#define TAILLE_PHRASE 1024

static int lire_ligne(const char *invite, char *texte, size_t taille)
{
	fputs(invite, stdout);
	fflush(stdout);
	if (fgets(texte, (int)taille, stdin) == NULL) {
		return 0;
	}

	size_t index = 0;
	while (texte[index] != '\0' && texte[index] != '\n') {
		index++;
	}
	if (texte[index] == '\n') {
		texte[index] = '\0';
		if (index > 0 && texte[index - 1] == '\r') {
			texte[index - 1] = '\0';
		}
	} else if (!feof(stdin)) {
		int caractere = getchar();
		if (caractere != '\n' && caractere != EOF) {
			while ((caractere = getchar()) != '\n' && caractere != EOF) {
			}
			return 0;
		}
	}

	return 1;
}

int main(int argc, char *argv[])
{
	char nom_saisi[TAILLE_NOM_FICHIER];
	char phrase[TAILLE_PHRASE];
	const char *nom_de_fichier;

	if (argc > 2) {
		fprintf(stderr, "Usage : %s [nom_de_fichier]\n", argv[0]);
		return 1;
	}
	if (argc == 2) {
		nom_de_fichier = argv[1];
	} else {
		if (!lire_ligne("Entrez le nom du fichier : ", nom_saisi, sizeof(nom_saisi))) {
			fprintf(stderr, "Nom de fichier invalide ou trop long.\n");
			return 1;
		}
		nom_de_fichier = nom_saisi;
	}
	if (!lire_ligne("Entrez la phrase que vous souhaitez rechercher : ",
			phrase, sizeof(phrase)) || phrase[0] == '\0') {
		fprintf(stderr, "Phrase invalide ou trop longue.\n");
		return 1;
	}

	FILE *flux = fopen(nom_de_fichier, "r");
	if (flux == NULL) {
		perror(nom_de_fichier);
		return 1;
	}

	char *ligne = NULL;
	size_t capacite = 0;
	size_t numero_ligne = 0;
	size_t nombre_lignes_trouvees = 0;
	ssize_t longueur_ligne;
	printf("Résultats de la recherche :\n");
	while ((longueur_ligne = getline(&ligne, &capacite, flux)) != -1) {
		(void)longueur_ligne;
		numero_ligne++;
		size_t occurrences = 0;
		const char *position = ligne;
		while ((position = strstr(position, phrase)) != NULL) {
			occurrences++;
			position++;
		}
		if (occurrences > 0) {
			printf("Ligne %zu, %zu fois\n", numero_ligne, occurrences);
			nombre_lignes_trouvees++;
		}
	}

	int erreur = ferror(flux);
	free(ligne);
	if (fclose(flux) != 0) {
		erreur = 1;
	}
	if (erreur) {
		perror(nom_de_fichier);
		return 1;
	}
	if (nombre_lignes_trouvees == 0) {
		printf("Aucune occurrence trouvée.\n");
	}

	return 0;
}
