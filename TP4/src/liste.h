#ifndef LISTE_H
#define LISTE_H

struct couleur {
	unsigned char rouge;
	unsigned char vert;
	unsigned char bleu;
	unsigned char alpha;
};

struct element_couleur {
	struct couleur couleur;
	struct element_couleur *suivant;
};

struct liste_couleurs {
	struct element_couleur *tete;
};

void init_liste(struct liste_couleurs *liste);
int insertion(const struct couleur *couleur, struct liste_couleurs *liste);
void parcours(const struct liste_couleurs *liste);
void detruire_liste(struct liste_couleurs *liste);

#endif
