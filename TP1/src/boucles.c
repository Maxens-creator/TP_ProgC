#include <stdio.h>

int main(void) {
    int compteur = 5;

    if (compteur <= 0 || compteur >= 10) {
        printf("Erreur : compteur doit être strictement positif et inférieur à 10.\n");
        return 1;
    }

    for (int i = 1; i <= compteur; i++) {
        for (int j = 1; j <= i; j++) {
            // Première colonne, dernière colonne de la ligne ou dernière ligne complète
            if (j == 1 || j == i || i == compteur) {
                printf("* ");
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }

    return 0;
}