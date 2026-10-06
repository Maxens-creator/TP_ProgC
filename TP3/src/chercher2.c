#include <stddef.h>
#include <stdio.h>

#define NOMBRE_PHRASES 10
#define TAILLE_RECHERCHE 256

int main(void)
{
	const char *phrases[NOMBRE_PHRASES] = {
		"Bonjour, comment ça va ?",
		"Le temps est magnifique aujourd'hui.",
		"C'est une belle journée.",
		"La programmation en C est amusante.",
		"Les tableaux en C sont puissants.",
		"Les pointeurs en C peuvent être déroutants.",
		"Il fait beau dehors.",
		"La recherche dans un tableau est intéressante.",
		"Les structures de données sont importantes.",
		"Programmer en C, c'est génial."
	};
	char recherche[TAILLE_RECHERCHE];
	int trouve = 0;

	printf("Entrez une phrase à rechercher : ");
	fflush(stdout);
	if (fgets(recherche, sizeof(recherche), stdin) == NULL) {
		fprintf(stderr, "Aucune phrase saisie.\n");
		return 1;
	}

	for (size_t index = 0; recherche[index] != '\0'; index++) {
		if (recherche[index] == '\n') {
			recherche[index] = '\0';
			break;
		}
	}

	for (size_t phrase_index = 0; phrase_index < NOMBRE_PHRASES; phrase_index++) {
		size_t caractere_index = 0;
		while (phrases[phrase_index][caractere_index] != '\0'
			&& recherche[caractere_index] != '\0'
			&& phrases[phrase_index][caractere_index] == recherche[caractere_index]) {
			caractere_index++;
		}

		if (phrases[phrase_index][caractere_index] == '\0'
			&& recherche[caractere_index] == '\0') {
			trouve = 1;
			break;
		}
	}

	if (trouve) {
		printf("Phrase trouvée\n");
	} else {
		printf("Phrase non trouvée\n");
	}

	return 0;
}