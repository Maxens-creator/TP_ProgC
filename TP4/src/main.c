#include <stdio.h>
#include <stddef.h>

#include "fichier.h"
#include "liste.h"
#include "operator.h"

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

static int exercice_4_2(void)
{
	int choix;
	char nom_de_fichier[256];
	char message[1024];

	printf("Que souhaitez-vous faire ?\n");
	printf("1. Lire un fichier\n");
	printf("2. Écrire dans un fichier\n");
	printf("Votre choix : ");
	if (scanf("%d", &choix) != 1) {
		fprintf(stderr, "Choix invalide.\n");
		return 1;
	}
	vider_fin_de_ligne();

	if (choix == 1) {
		if (!lire_ligne("Entrez le nom du fichier à lire : ",
				nom_de_fichier, sizeof(nom_de_fichier))) {
			fprintf(stderr, "Nom de fichier invalide ou trop long.\n");
			return 1;
		}
		return lire_fichier(nom_de_fichier) ? 0 : 1;
	}
	if (choix == 2) {
		if (!lire_ligne("Entrez le nom du fichier dans lequel vous souhaitez écrire : ",
				nom_de_fichier, sizeof(nom_de_fichier))
			|| !lire_ligne("Entrez le message à écrire : ", message, sizeof(message))) {
			fprintf(stderr, "Saisie invalide ou trop longue.\n");
			return 1;
		}
		return ecrire_dans_fichier(nom_de_fichier, message) ? 0 : 1;
	}

	fprintf(stderr, "Choix invalide.\n");
	return 1;
}

static int exercice_4_7(void)
{
	const struct couleur couleurs[] = {
		{0xff, 0x00, 0x00, 0xff},
		{0x00, 0xff, 0x00, 0xff},
		{0x00, 0x00, 0xff, 0xff},
		{0xff, 0xff, 0xff, 0xff},
		{0x00, 0x00, 0x00, 0xff},
		{0xff, 0xff, 0x00, 0xff},
		{0x00, 0xff, 0xff, 0xff},
		{0xff, 0x00, 0xff, 0xff},
		{0xff, 0x80, 0x00, 0xff},
		{0x80, 0x80, 0x80, 0xff}
	};
	const size_t nombre_couleurs = sizeof(couleurs) / sizeof(couleurs[0]);
	struct liste_couleurs liste;
	init_liste(&liste);

	for (size_t index = 0; index < nombre_couleurs; index++) {
		if (!insertion(&couleurs[index], &liste)) {
			fprintf(stderr, "Impossible d'ajouter une couleur à la liste.\n");
			detruire_liste(&liste);
			return 1;
		}
	}

	printf("Liste des couleurs :\n");
	parcours(&liste);
	detruire_liste(&liste);
	return 0;
}

int main(void)
{
	int choix;

	printf("Choisissez l'exercice :\n");
	printf("1. Calcul avec opérateurs\n");
	printf("2. Gestion de fichiers\n");
	printf("7. Gestion d'une liste de couleurs\n");
	printf("Votre choix : ");
	if (scanf("%d", &choix) != 1) {
		fprintf(stderr, "Choix invalide.\n");
		return 1;
	}

	switch (choix) {
	case 1:
		return exercice_4_1();
	case 2:
		return exercice_4_2();
	case 7:
		return exercice_4_7();
	default:
		fprintf(stderr, "Exercice invalide.\n");
		return 1;
	}
}

