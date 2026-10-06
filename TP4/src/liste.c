#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

void init_liste(struct liste_couleurs *liste)
{
	if (liste != NULL) {
		liste->tete = NULL;
	}
}

int insertion(const struct couleur *couleur, struct liste_couleurs *liste)
{
	if (couleur == NULL || liste == NULL) {
		return 0;
	}

	struct element_couleur *nouvel_element = malloc(sizeof(*nouvel_element));
	if (nouvel_element == NULL) {
		return 0;
	}
	nouvel_element->couleur = *couleur;
	nouvel_element->suivant = NULL;

	struct element_couleur **position = &liste->tete;
	while (*position != NULL) {
		position = &(*position)->suivant;
	}
	*position = nouvel_element;
	return 1;
}

void parcours(const struct liste_couleurs *liste)
{
	if (liste == NULL) {
		return;
	}

	for (const struct element_couleur *element = liste->tete;
		element != NULL; element = element->suivant) {
		printf("0x%02x 0x%02x 0x%02x 0x%02x\n",
			(unsigned int)element->couleur.rouge,
			(unsigned int)element->couleur.vert,
			(unsigned int)element->couleur.bleu,
			(unsigned int)element->couleur.alpha);
	}
}

void detruire_liste(struct liste_couleurs *liste)
{
	if (liste == NULL) {
		return;
	}

	struct element_couleur *element = liste->tete;
	while (element != NULL) {
		struct element_couleur *suivant = element->suivant;
		free(element);
		element = suivant;
	}
	liste->tete = NULL;
}
