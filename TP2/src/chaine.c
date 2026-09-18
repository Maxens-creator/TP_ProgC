#include <stdio.h>

int main(void) {
    char source[] = "Bonjour";
    char copie[50];
    char destination[100] = "Hello, ";
    char ajout[] = "ESIEE-IT !";

    // 1. Calcul de la longueur de la chaîne "source"
    int longueur = 0;
    while (source[longueur] != '\0') {
        longueur++;
    }
    printf("Longueur de \"%s\" : %d\n\n", source, longueur);

    // 2. Copie de "source" vers "copie"
    int i = 0;
    while (source[i] != '\0') {
        copie[i] = source[i];
        i++;
    }
    copie[i] = '\0'; // Caractère nul terminal obligatoire
    printf("Chaîne copiée : \"%s\"\n\n", copie);

    // 3. Concaténation de "ajout" à la suite de "destination"
    // Trouver d'abord la fin de la première chaîne
    int dest_len = 0;
    while (destination[dest_len] != '\0') {
        dest_len++;
    }

    // Ajouter les caractères de la deuxième chaîne à partir de cet emplacement
    int j = 0;
    while (ajout[j] != '\0') {
        destination[dest_len + j] = ajout[j];
        j++;
    }
    destination[dest_len + j] = '\0'; // Caractère nul terminal obligatoire
    printf("Chaîne concaténée : \"%s\"\n", destination);

    return 0;
}