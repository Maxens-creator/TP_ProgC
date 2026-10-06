#include <stdio.h>

static unsigned long long factorielle(unsigned int nombre)
{
	if (nombre <= 1) {
		return 1;
	}
	return nombre * factorielle(nombre - 1);
}

int main(void)
{
	const unsigned int valeurs[] = {0, 1, 5, 10, 20};
	const size_t nombre_valeurs = sizeof(valeurs) / sizeof(valeurs[0]);

	for (size_t index = 0; index < nombre_valeurs; index++) {
		printf("%u! = %llu\n", valeurs[index], factorielle(valeurs[index]));
	}

	return 0;
}
