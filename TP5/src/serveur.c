/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define _POSIX_C_SOURCE 200809L

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "serveur.h"

static int socketfd = -1;

static int envoyer_tout(int client_socket_fd, const char *donnees, size_t taille)
{
	size_t envoyes = 0;
	while (envoyes < taille) {
		ssize_t resultat = send(client_socket_fd, donnees + envoyes,
			taille - envoyes, MSG_NOSIGNAL);
		if (resultat < 0 && errno == EINTR) {
			continue;
		}
		if (resultat <= 0) {
			return -1;
		}
		envoyes += (size_t)resultat;
	}
	return 0;
}

static int recevoir_ligne(int client_socket_fd, char *message, size_t taille)
{
	size_t longueur = 0;
	while (longueur < taille - 1) {
		char caractere;
		ssize_t resultat = recv(client_socket_fd, &caractere, 1, 0);
		if (resultat < 0 && errno == EINTR) {
			continue;
		}
		if (resultat < 0) {
			return -1;
		}
		if (resultat == 0) {
			if (longueur == 0) {
				return 0;
			}
			break;
		}
		if (caractere == '\n') {
			break;
		}
		message[longueur++] = caractere;
	}
	message[longueur] = '\0';
	return longueur == taille - 1 ? -1 : 1;
}

int renvoie_message(int client_socket_fd, const char *message)
{
	if (envoyer_tout(client_socket_fd, message, strlen(message)) != 0
		|| envoyer_tout(client_socket_fd, "\n", 1) != 0) {
		perror("Erreur d'écriture");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int recois_envoie_message(int client_socket_fd, const char *message)
{
	if (strncmp(message, "message: ", 9) != 0) {
		fprintf(stderr, "Format de message invalide.\n");
		return EXIT_FAILURE;
	}

	printf("Message reçu: %s\n", message);
	fflush(stdout);
	char saisie[TAILLE_MESSAGE];
	char reponse[TAILLE_MESSAGE];
	printf("Votre réponse au client : ");
	fflush(stdout);
	if (fgets(saisie, sizeof(saisie), stdin) == NULL) {
		fprintf(stderr, "Aucune réponse saisie.\n");
		return EXIT_FAILURE;
	}
	saisie[strcspn(saisie, "\r\n")] = '\0';

	int longueur = snprintf(reponse, sizeof(reponse), "message: %s", saisie);
	if (longueur < 0 || (size_t)longueur >= sizeof(reponse)) {
		fprintf(stderr, "Réponse trop longue.\n");
		return EXIT_FAILURE;
	}
	return renvoie_message(client_socket_fd, reponse);
}

static void gestionnaire_ctrl_c(int signal_recu)
{
	(void)signal_recu;
	static const char message[] = "\nSignal Ctrl+C capturé. Sortie du programme.\n";
	if (socketfd != -1) {
		close(socketfd);
	}
	(void)write(STDOUT_FILENO, message, sizeof(message) - 1);
	_exit(EXIT_SUCCESS);
}

static void gerer_client(int client_socket_fd)
{
	char message[TAILLE_MESSAGE];
	int statut;
	while ((statut = recevoir_ligne(client_socket_fd, message, sizeof(message))) > 0) {
		if (recois_envoie_message(client_socket_fd, message) != EXIT_SUCCESS) {
			break;
		}
	}
	if (statut < 0) {
		fprintf(stderr, "Erreur de réception ou message trop long.\n");
	}
	printf("Client déconnecté.\n");
}

int main(void)
{
	int option = 1;
	struct sockaddr_in adresse_serveur;

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0) {
		perror("socket");
		return EXIT_FAILURE;
	}
	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0) {
		perror("setsockopt");
		close(socketfd);
		return EXIT_FAILURE;
	}

	memset(&adresse_serveur, 0, sizeof(adresse_serveur));
	adresse_serveur.sin_family = AF_INET;
	adresse_serveur.sin_port = htons(PORT);
	adresse_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socketfd, (struct sockaddr *)&adresse_serveur, sizeof(adresse_serveur)) < 0) {
		perror("bind");
		close(socketfd);
		return EXIT_FAILURE;
	}
	if (listen(socketfd, 10) < 0) {
		perror("listen");
		close(socketfd);
		return EXIT_FAILURE;
	}
	if (signal(SIGINT, gestionnaire_ctrl_c) == SIG_ERR) {
		perror("signal");
		close(socketfd);
		return EXIT_FAILURE;
	}

	printf("Serveur en attente de connexions...\n");
	fflush(stdout);
	for (;;) {
		struct sockaddr_in adresse_client;
		socklen_t longueur_adresse = sizeof(adresse_client);
		int client_socket_fd = accept(socketfd,
			(struct sockaddr *)&adresse_client, &longueur_adresse);
		if (client_socket_fd < 0) {
			if (errno == EINTR) {
				continue;
			}
			perror("accept");
			continue;
		}

		gerer_client(client_socket_fd);
		close(client_socket_fd);
	}
}