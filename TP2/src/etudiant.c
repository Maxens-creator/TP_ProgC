#include <stdio.h>

int main(void)
{
	const char noms_prenoms[5][2][30] = {
		{"Dupont", "Marie"},
		{"Martin", "Pierre"},
		{"Bernard", "Sophie"},
		{"Robert", "Lucas"},
		{"Petit", "Emma"}
	};
	const char adresses[5][80] = {
		"20, Boulevard Niels Bohr, Lyon",
		"22, Boulevard Niels Bohr, Lyon",
		"10, Rue de la Republique, Lille",
		"5, Avenue Victor Hugo, Paris",
		"8, Rue des Ecoles, Nantes"
	};
	const float notes_programmation[5] = {16.5f, 14.0f, 12.5f, 17.0f, 15.5f};
	const float notes_systeme_exploitation[5] = {
		12.1f, 14.1f, 13.5f, 15.0f, 16.0f
	};

	for (int i = 0; i < 5; i++) {
		printf("Etudiant.e %d :\n", i + 1);
		printf("Nom : %s\n", noms_prenoms[i][0]);
		printf("Prenom : %s\n", noms_prenoms[i][1]);
		printf("Adresse : %s\n", adresses[i]);
		printf("Note en Programmation en C : %.1f\n", notes_programmation[i]);
		printf("Note en Systeme d'exploitation : %.1f\n\n",
			   notes_systeme_exploitation[i]);
	}

	return 0;
}
