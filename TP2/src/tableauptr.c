#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_TABLEAU 11

static void remplir_entiers(int *tableau, int taille)
{
	int *curseur = tableau;
	int *fin = tableau + taille;

	while (curseur < fin) {
		*curseur = rand() % 100 + 1;
		curseur++;
	}
}

static void remplir_flottants(float *tableau, int taille)
{
	float *curseur = tableau;
	float *fin = tableau + taille;

	while (curseur < fin) {
		*curseur = (float)(rand() % 1000 + 1) / 100.0f;
		curseur++;
	}
}

static void afficher_entiers(const int *tableau, int taille)
{
	const int *curseur = tableau;
	const int *fin = tableau + taille;

	while (curseur < fin) {
		printf("%d", *curseur);
		curseur++;
		if (curseur < fin) {
			printf(", ");
		}
	}
	printf("\n");
}

static void afficher_flottants(const float *tableau, int taille)
{
	const float *curseur = tableau;
	const float *fin = tableau + taille;

	while (curseur < fin) {
		printf("%.2f", *curseur);
		curseur++;
		if (curseur < fin) {
			printf(", ");
		}
	}
	printf("\n");
}

static void multiplier_entiers_pairs(int *tableau, int taille)
{
	int *curseur = tableau;
	int indice = 0;

	while (curseur < tableau + taille) {
		if (indice % 2 == 0) {
			*curseur *= 3;
		}
		curseur++;
		indice++;
	}
}

static void multiplier_flottants_pairs(float *tableau, int taille)
{
	float *curseur = tableau;
	int indice = 0;

	while (curseur < tableau + taille) {
		if (indice % 2 == 0) {
			*curseur *= 3.0f;
		}
		curseur++;
		indice++;
	}
}

int main(void)
{
	int tableau_entiers[TAILLE_TABLEAU];
	float tableau_flottants[TAILLE_TABLEAU];

	srand((unsigned int)time(NULL));
	remplir_entiers(tableau_entiers, TAILLE_TABLEAU);
	remplir_flottants(tableau_flottants, TAILLE_TABLEAU);

	printf("Tableau d'entiers (avant la multiplication par 3) :\n");
	afficher_entiers(tableau_entiers, TAILLE_TABLEAU);
	printf("Tableau de nombres a virgule flottante (avant la multiplication par 3) :\n");
	afficher_flottants(tableau_flottants, TAILLE_TABLEAU);

	multiplier_entiers_pairs(tableau_entiers, TAILLE_TABLEAU);
	multiplier_flottants_pairs(tableau_flottants, TAILLE_TABLEAU);

	printf("\nTableau d'entiers (apres la multiplication par 3) :\n");
	afficher_entiers(tableau_entiers, TAILLE_TABLEAU);
	printf("Tableau de nombres a virgule flottante (apres la multiplication par 3) :\n");
	afficher_flottants(tableau_flottants, TAILLE_TABLEAU);

	return 0;
}
