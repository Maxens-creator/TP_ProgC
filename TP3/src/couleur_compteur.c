#include <stddef.h>
#include <stdio.h>

#define TAILLE 100

typedef struct {
	unsigned char rouge;
	unsigned char vert;
	unsigned char bleu;
	unsigned char alpha;
} Couleur;

typedef struct {
	Couleur couleur;
	size_t occurrences;
} CouleurDistincte;

static int couleurs_egales(Couleur premiere, Couleur seconde)
{
	return premiere.rouge == seconde.rouge
		&& premiere.vert == seconde.vert
		&& premiere.bleu == seconde.bleu
		&& premiere.alpha == seconde.alpha;
}

int main(void)
{
	const Couleur palette[] = {
		{0xff, 0x23, 0x23, 0x45},
		{0xff, 0x00, 0x23, 0x12},
		{0x00, 0x80, 0xff, 0xff},
		{0x12, 0x34, 0x56, 0x78}
	};
	const size_t motif[] = {0, 1, 0, 2, 0, 1, 3, 0, 2, 1};
	Couleur couleurs[TAILLE];
	CouleurDistincte distinctes[TAILLE];
	size_t nombre_distinctes = 0;

	for (size_t index = 0; index < TAILLE; index++) {
		couleurs[index] = palette[motif[index % (sizeof(motif) / sizeof(motif[0]))]];
	}

	for (size_t index = 0; index < TAILLE; index++) {
		size_t couleur_index = 0;
		while (couleur_index < nombre_distinctes
			&& !couleurs_egales(couleurs[index], distinctes[couleur_index].couleur)) {
			couleur_index++;
		}

		if (couleur_index == nombre_distinctes) {
			distinctes[couleur_index].couleur = couleurs[index];
			distinctes[couleur_index].occurrences = 0;
			nombre_distinctes++;
		}
		distinctes[couleur_index].occurrences++;
	}

	for (size_t index = 0; index < nombre_distinctes; index++) {
		Couleur couleur = distinctes[index].couleur;
		printf("0x%02x 0x%02x 0x%02x 0x%02x : %zu\n",
			(unsigned int)couleur.rouge,
			(unsigned int)couleur.vert,
			(unsigned int)couleur.bleu,
			(unsigned int)couleur.alpha,
			distinctes[index].occurrences);
	}

	return 0;
}
