#include <stdio.h>
#include <string.h>

typedef struct {
	char nom[30];
	char prenom[30];
	char adresse[80];
	float note_programmation;
	float note_systeme_exploitation;
} Etudiant;

int main(void)
{
	Etudiant etudiants[5];

	strcpy(etudiants[0].nom, "Dupont");
	strcpy(etudiants[0].prenom, "Marie");
	strcpy(etudiants[0].adresse, "20, Boulevard Niels Bohr, Lyon");
	etudiants[0].note_programmation = 16.5f;
	etudiants[0].note_systeme_exploitation = 12.1f;

	strcpy(etudiants[1].nom, "Martin");
	strcpy(etudiants[1].prenom, "Pierre");
	strcpy(etudiants[1].adresse, "22, Boulevard Niels Bohr, Lyon");
	etudiants[1].note_programmation = 14.0f;
	etudiants[1].note_systeme_exploitation = 14.1f;

	strcpy(etudiants[2].nom, "Bernard");
	strcpy(etudiants[2].prenom, "Sophie");
	strcpy(etudiants[2].adresse, "10, Rue de la Republique, Lille");
	etudiants[2].note_programmation = 12.5f;
	etudiants[2].note_systeme_exploitation = 13.5f;

	strcpy(etudiants[3].nom, "Robert");
	strcpy(etudiants[3].prenom, "Lucas");
	strcpy(etudiants[3].adresse, "5, Avenue Victor Hugo, Paris");
	etudiants[3].note_programmation = 17.0f;
	etudiants[3].note_systeme_exploitation = 15.0f;

	strcpy(etudiants[4].nom, "Petit");
	strcpy(etudiants[4].prenom, "Emma");
	strcpy(etudiants[4].adresse, "8, Rue des Ecoles, Nantes");
	etudiants[4].note_programmation = 15.5f;
	etudiants[4].note_systeme_exploitation = 16.0f;

	for (int i = 0; i < 5; i++) {
		printf("Etudiant.e %d :\n", i + 1);
		printf("Nom : %s\n", etudiants[i].nom);
		printf("Prenom : %s\n", etudiants[i].prenom);
		printf("Adresse : %s\n", etudiants[i].adresse);
		printf("Note en Programmation en C : %.1f\n",
		       etudiants[i].note_programmation);
		printf("Note en Systeme d'exploitation : %.1f\n\n",
		       etudiants[i].note_systeme_exploitation);
	}

	return 0;
}
