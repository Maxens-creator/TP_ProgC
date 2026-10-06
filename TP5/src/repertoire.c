#include <dirent.h>
#include <errno.h>
#include <stdio.h>

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

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Utilisation : %s <nom_du_repertoire>\n", argv[0]);
		return 1;
	}

	return lire_dossier(argv[1]) == 0 ? 0 : 1;
}
