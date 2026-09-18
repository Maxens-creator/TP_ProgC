#include <stdio.h>
#include <stddef.h>

static void afficher_variable(const char *nom, const void *adresse,
				      size_t taille)
{
	const unsigned char *octets = adresse;

	printf("Adresse de %s : %p, Valeur de %s : 0x", nom, adresse, nom);
	for (size_t i = taille; i > 0; i--) {
		printf("%02x", octets[i - 1]);
	}
	printf("\n");
}

static void afficher_etat(const char *titre,
				  char *pc, short *ps, int *pi, long int *pli,
				  long long int *plli, float *pf, double *pd,
				  long double *pld)
{
	printf("%s\n", titre);
	afficher_variable("char", pc, sizeof(*pc));
	afficher_variable("short", ps, sizeof(*ps));
	afficher_variable("int", pi, sizeof(*pi));
	afficher_variable("long int", pli, sizeof(*pli));
	afficher_variable("long long int", plli, sizeof(*plli));
	afficher_variable("float", pf, sizeof(*pf));
	afficher_variable("double", pd, sizeof(*pd));
	afficher_variable("long double", pld, sizeof(*pld));
	printf("\n");
}

int main(void)
{
	char c = 'A';
	short s = -32000;
	int i = -100000;
	long int li = -2000000000L;
	long long int lli = -9000000000000000000LL;
	float f = 3.14f;
	double d = 2.7182818284;
	long double ld = 1.4142135623730950488L;

	char *pc = &c;
	short *ps = &s;
	int *pi = &i;
	long int *pli = &li;
	long long int *plli = &lli;
	float *pf = &f;
	double *pd = &d;
	long double *pld = &ld;

	afficher_etat("Avant la manipulation :", pc, ps, pi, pli, plli, pf, pd,
		       pld);

	*pc = 'B';
	*ps = -31000;
	*pi = -99999;
	*pli = -1999999999L;
	*plli = -8999999999999999999LL;
	*pf = 1.0f;
	*pd = 3.0;
	*pld = 2.0L;

	afficher_etat("Apres la manipulation :", pc, ps, pi, pli, plli, pf, pd,
		       pld);

	return 0;
}
