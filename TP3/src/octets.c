#include <stddef.h>
#include <stdio.h>

static void afficher_octets(const char *type, const void *adresse, size_t taille)
{
	const unsigned char *octets = adresse;

	printf("Octets de %s :\n", type);
	for (size_t index = 0; index < taille; index++) {
		printf(" %02x", (unsigned int)*(octets + index));
	}
	printf("\n\n");
}

int main(void)
{
	short valeur_short = 0x1234;
	int valeur_int = 0x12345678;
	long int valeur_long = 0x12345678L;
	float valeur_float = 3.14f;
	double valeur_double = 3.14;
	long double valeur_long_double = 3.14L;
	unsigned int test_ordre = 1;
	const unsigned char *octets_test = (const unsigned char *)&test_ordre;

	if (*octets_test == 1) {
		printf("Ordre des octets : petit-boutiste\n\n");
	} else {
		printf("Ordre des octets : gros-boutiste\n\n");
	}

	afficher_octets("short", &valeur_short, sizeof(valeur_short));
	afficher_octets("int", &valeur_int, sizeof(valeur_int));
	afficher_octets("long int", &valeur_long, sizeof(valeur_long));
	afficher_octets("float", &valeur_float, sizeof(valeur_float));
	afficher_octets("double", &valeur_double, sizeof(valeur_double));
	afficher_octets("long double", &valeur_long_double, sizeof(valeur_long_double));

	return 0;
}
