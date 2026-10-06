/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#define _POSIX_C_SOURCE 200809L

#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"

static int envoyer_tout(int socketfd, const char *donnees, size_t taille)
{
  size_t envoyes = 0;
  while (envoyes < taille) {
    ssize_t resultat = send(socketfd, donnees + envoyes, taille - envoyes,
      MSG_NOSIGNAL);
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

static int envoyer_ligne(int socketfd, const char *message)
{
  if (envoyer_tout(socketfd, message, strlen(message)) != 0
    || envoyer_tout(socketfd, "\n", 1) != 0) {
    perror("Erreur d'écriture");
    return -1;
  }
  return 0;
}

static int recevoir_ligne(int socketfd, char *message, size_t taille)
{
  size_t longueur = 0;
  while (longueur < taille - 1) {
    char caractere;
    ssize_t resultat = recv(socketfd, &caractere, 1, 0);
    if (resultat < 0 && errno == EINTR) {
      continue;
    }
    if (resultat < 0) {
      perror("Erreur de lecture");
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
  if (longueur == taille - 1) {
    fprintf(stderr, "Message reçu trop long.\n");
    return -1;
  }
  return 1;
}

static int lire_note_fichier(const char *repertoire, int numero_etudiant,
    int numero_note, double *note)
{
  char chemin[512];
  int longueur = snprintf(chemin, sizeof(chemin), "%s/%d/note%d.txt",
    repertoire, numero_etudiant, numero_note);
  if (longueur < 0 || (size_t)longueur >= sizeof(chemin)) {
    fprintf(stderr, "Chemin de note trop long.\n");
    return 0;
  }

  FILE *flux = fopen(chemin, "r");
  if (flux == NULL) {
    perror(chemin);
    return 0;
  }
  int succes = fscanf(flux, "%lf", note) == 1 && isfinite(*note);
  if (fclose(flux) != 0) {
    succes = 0;
  }
  if (!succes) {
    fprintf(stderr, "Note invalide dans %s.\n", chemin);
  }
  return succes;
}

static int envoyer_notes(int socketfd, const char *repertoire)
{
  double somme_moyennes = 0.0;
  for (int numero_etudiant = 1; numero_etudiant <= 5; numero_etudiant++) {
    double somme_notes = 0.0;
    for (int numero_note = 1; numero_note <= 5; numero_note++) {
      double note;
      if (!lire_note_fichier(repertoire, numero_etudiant, numero_note, &note)
        || envoie_operateur_numeros(socketfd, '+', somme_notes,
          note, &somme_notes) != 0) {
        return -1;
      }
    }

    double moyenne_etudiant;
    if (envoie_operateur_numeros(socketfd, '/', somme_notes, 5.0,
        &moyenne_etudiant) != 0) {
      return -1;
    }
    printf("Moyenne étudiant %d : %.10g\n",
      numero_etudiant, moyenne_etudiant);
    if (envoie_operateur_numeros(socketfd, '+', somme_moyennes,
        moyenne_etudiant, &somme_moyennes) != 0) {
      return -1;
    }
  }

  double moyenne_classe;
  if (envoie_operateur_numeros(socketfd, '/', somme_moyennes, 5.0,
      &moyenne_classe) != 0) {
    return -1;
  }
  printf("Moyenne de la classe : %.10g\n", moyenne_classe);
  return 0;
}

/**
 * Fonction pour envoyer et recevoir un message depuis un client connecté à la socket.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_recois_message(int socketfd)
{
  char message[1002];
  char requete[TAILLE_MESSAGE];
  char reponse[TAILLE_MESSAGE];

  printf("Votre message (max 1000 caractères): ");
  fflush(stdout);
  if (fgets(message, sizeof(message), stdin) == NULL) {
    return 1;
  }

  size_t longueur = strcspn(message, "\r\n");
  if (message[longueur] == '\r' || message[longueur] == '\n') {
    message[longueur] = '\0';
  } else if (!feof(stdin)) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
    fprintf(stderr, "Message trop long.\n");
    return -1;
  }
  if (strcmp(message, "quitter") == 0) {
    return 1;
  }
  if (strcmp(message, "notes") == 0) {
    return envoyer_notes(socketfd, "../etudiant");
  }

  if (strncmp(message, "calcule :", 9) == 0) {
    char operateur;
    double num1;
    double num2;
    char texte_supplementaire;
    if (sscanf(message, "calcule : %c %lf %lf %c", &operateur,
        &num1, &num2, &texte_supplementaire) != 3) {
      fprintf(stderr, "Format attendu : calcule : <opérateur> <num1> <num2>\n");
      return -1;
    }
    return envoie_operateur_numeros(socketfd, operateur, num1, num2, NULL);
  }

  int taille_requete = snprintf(requete, sizeof(requete), "message: %s", message);
  if (taille_requete < 0 || (size_t)taille_requete >= sizeof(requete)
    || envoyer_ligne(socketfd, requete) != 0) {
    return -1;
  }

  int statut = recevoir_ligne(socketfd, reponse, sizeof(reponse));
  if (statut <= 0) {
    return -1;
  }
  printf("Message reçu: %s\n", reponse);
  return 0;
}

int envoie_operateur_numeros(int socketfd, char operateur, double num1, double num2,
    double *resultat)
{
  char requete[TAILLE_MESSAGE];
  char reponse[TAILLE_MESSAGE];
  int longueur = snprintf(requete, sizeof(requete), "calcule : %c %.17g %.17g",
  operateur, num1, num2);
  if (longueur < 0 || (size_t)longueur >= sizeof(requete)
  || envoyer_ligne(socketfd, requete) != 0) {
  return -1;
  }

  int statut = recevoir_ligne(socketfd, reponse, sizeof(reponse));
  if (statut <= 0) {
  return -1;
  }
  char texte_supplementaire;
  double valeur_resultat;
  if (sscanf(reponse, "calcule : %lf %c", &valeur_resultat,
    &texte_supplementaire) != 1) {
    fprintf(stderr, "Réponse de calcul invalide : %s\n", reponse);
    return -1;
  }
  if (resultat != NULL) {
    *resultat = valeur_resultat;
  }
  printf("%s\n", reponse);
  return 0;
}

int main(int argc, char *argv[])
{
  const char *repertoire_etudiants = "../etudiant";
  int mode_notes = 0;
  if (argc == 2 && strcmp(argv[1], "--notes") == 0) {
    mode_notes = 1;
  } else if (argc == 3 && strcmp(argv[1], "--notes") == 0) {
    mode_notes = 1;
    repertoire_etudiants = argv[2];
  } else if (argc != 1) {
    fprintf(stderr, "Usage : %s [--notes [dossier_etudiants]]\n", argv[0]);
    return EXIT_FAILURE;
  }

  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0) {
    perror("socket");
    return EXIT_FAILURE;
  }

  struct sockaddr_in adresse_serveur;
  memset(&adresse_serveur, 0, sizeof(adresse_serveur));
  adresse_serveur.sin_family = AF_INET;
  adresse_serveur.sin_port = htons(PORT);
  if (inet_pton(AF_INET, "127.0.0.1", &adresse_serveur.sin_addr) != 1) {
    fprintf(stderr, "Adresse serveur invalide.\n");
    close(socketfd);
    return EXIT_FAILURE;
  }

  if (connect(socketfd, (struct sockaddr *)&adresse_serveur,
      sizeof(adresse_serveur)) < 0) {
    perror("connection serveur");
    close(socketfd);
    return EXIT_FAILURE;
  }

  if (mode_notes) {
    int statut_notes = envoyer_notes(socketfd, repertoire_etudiants);
    close(socketfd);
    return statut_notes == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
  }

  int statut;
  do {
    statut = envoie_recois_message(socketfd);
  } while (statut == 0);

  close(socketfd);
  return statut < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
