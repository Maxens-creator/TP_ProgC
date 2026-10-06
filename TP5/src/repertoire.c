#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "repertoire.h"

int lire_dossier(const char *nom_repertoire)
{
	DIR *dossier = opendir(nom_repertoire);
	if (dossier == NULL) {
		perror(nom_repertoire);
		return -1;
	}

	struct dirent *entree;
	int statut = 0;
	errno = 0;
	while ((entree = readdir(dossier)) != NULL) {
		if (entree->d_name[0] == '.'
			&& (entree->d_name[1] == '\0'
				|| (entree->d_name[1] == '.' && entree->d_name[2] == '\0'))) {
			continue;
		}
		printf("%s\n", entree->d_name);
	}
	if (errno != 0) {
		perror(nom_repertoire);
		statut = -1;
	}
	if (closedir(dossier) != 0) {
		perror(nom_repertoire);
		statut = -1;
	}

	return statut;
}

static char *construire_chemin(const char *repertoire, const char *nom)
{
	size_t longueur_repertoire = strlen(repertoire);
	size_t longueur_nom = strlen(nom);
	int separateur = longueur_repertoire > 0
		&& repertoire[longueur_repertoire - 1] != '/';
	char *chemin = malloc(longueur_repertoire + (size_t)separateur
		+ longueur_nom + 1);
	if (chemin == NULL) {
		return NULL;
	}

	snprintf(chemin, longueur_repertoire + (size_t)separateur + longueur_nom + 1,
		"%s%s%s", repertoire, separateur ? "/" : "", nom);
	return chemin;
}

static int lire_dossier_recursif_interne(const char *nom_repertoire)
{
	DIR *dossier = opendir(nom_repertoire);
	if (dossier == NULL) {
		perror(nom_repertoire);
		return -1;
	}

	int statut = 0;
	struct dirent *entree;
	for (;;) {
		errno = 0;
		entree = readdir(dossier);
		if (entree == NULL) {
			if (errno != 0) {
				perror(nom_repertoire);
				statut = -1;
			}
			break;
		}
		if (entree->d_name[0] == '.'
			&& (entree->d_name[1] == '\0'
				|| (entree->d_name[1] == '.' && entree->d_name[2] == '\0'))) {
			continue;
		}

		char *chemin = construire_chemin(nom_repertoire, entree->d_name);
		if (chemin == NULL) {
			perror("malloc");
			statut = -1;
			continue;
		}
		printf("%s\n", chemin);

		struct stat informations;
		if (lstat(chemin, &informations) != 0) {
			perror(chemin);
			statut = -1;
		} else if (S_ISDIR(informations.st_mode)
			&& lire_dossier_recursif_interne(chemin) != 0) {
			statut = -1;
		}
		free(chemin);
	}

	if (closedir(dossier) != 0) {
		perror(nom_repertoire);
		statut = -1;
	}
	return statut;
}

int lire_dossier_recursif(const char *nom_repertoire)
{
	return lire_dossier_recursif_interne(nom_repertoire);
}

int main(int argc, char *argv[])
{
	if (argc == 2) {
		return lire_dossier(argv[1]) == 0 ? 0 : 1;
	}
	if (argc == 3 && strcmp(argv[2], "--recursive") == 0) {
		return lire_dossier_recursif(argv[1]) == 0 ? 0 : 1;
	}
	fprintf(stderr, "Utilisation : %s <nom_du_repertoire> [--recursive]\n", argv[0]);
	return 1;
}
