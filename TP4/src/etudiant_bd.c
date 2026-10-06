#include <stdio.h>
#include <stddef.h>

#include "fichier.h"

#define NOMBRE_ETUDIANTS 5
#define TAILLE_ADRESSE 120

typedef struct {
	char nom[30];
	char prenom[30];
	char adresse[TAILLE_ADRESSE];
	float note_programmation;
	float note_systeme_exploitation;
} Etudiant;

static int lire_ligne(const char *invite, char *texte, size_t taille)
{
	fputs(invite, stdout);
	if (fgets(texte, (int)taille, stdin) == NULL) {
		return 0;
	}

	size_t index = 0;
	while (texte[index] != '\0' && texte[index] != '\n') {
		index++;
	}
	if (texte[index] == '\n') {
		texte[index] = '\0';
	} else {
		int caractere = getchar();
		if (caractere != '\n' && caractere != EOF) {
			while ((caractere = getchar()) != '\n' && caractere != EOF) {
			}
			return 0;
		}
	}

	return 1;
}

static void vider_fin_de_ligne(void)
{
	int caractere;
	while ((caractere = getchar()) != '\n' && caractere != EOF) {
	}
}

static int lire_note(const char *invite, float *note)
{
	fputs(invite, stdout);
	if (scanf("%f", note) != 1) {
		return 0;
	}
	vider_fin_de_ligne();
	return 1;
}

int main(void)
{
	Etudiant etudiants[NOMBRE_ETUDIANTS];
	const char *nom_de_fichier = "etudiant.txt";
	char ligne[256];

	for (size_t index = 0; index < NOMBRE_ETUDIANTS; index++) {
		printf("Entrez les détails de l'étudiant.e %zu :\n", index + 1);
		if (!lire_ligne("Nom : ", etudiants[index].nom, sizeof(etudiants[index].nom))
			|| !lire_ligne("Prénom : ", etudiants[index].prenom,
				sizeof(etudiants[index].prenom))
			|| !lire_ligne("Adresse : ", etudiants[index].adresse,
				sizeof(etudiants[index].adresse))
			|| !lire_note("Note en programmation : ",
				&etudiants[index].note_programmation)
			|| !lire_note("Note en système d'exploitation : ",
				&etudiants[index].note_systeme_exploitation)) {
			fprintf(stderr, "Saisie invalide ou trop longue.\n");
			return 1;
		}
	}

	for (size_t index = 0; index < NOMBRE_ETUDIANTS; index++) {
		int longueur = snprintf(ligne, sizeof(ligne), "%s;%s;%s;%.2f;%.2f",
			etudiants[index].nom,
			etudiants[index].prenom,
			etudiants[index].adresse,
			(double)etudiants[index].note_programmation,
			(double)etudiants[index].note_systeme_exploitation);
		if (longueur < 0 || (size_t)longueur >= sizeof(ligne)) {
			fprintf(stderr, "Données étudiant trop longues.\n");
			return 1;
		}

		int succes = index == 0
			? ecrire_dans_fichier(nom_de_fichier, ligne)
			: ajouter_dans_fichier(nom_de_fichier, ligne);
		if (!succes) {
			return 1;
		}
	}

	printf("Les détails des étudiants ont été enregistrés dans le fichier %s.\n",
		nom_de_fichier);
	return 0;
}
