#include <stdio.h>

int main(void) {
    int compteur = 5;

    if (compteur <= 0 || compteur >= 10) {
        printf("Erreur : compteur doit être strictement positif et inférieur à 10.\n");
        return 1;
    }

    int i = 1;
    while (i <= compteur) {
        int j = 1;
        while (j <= i) {
            if (j == 1 || j == i || i == compteur) {
                printf("* ");
            } else {
                printf("# ");
            }
            j++;
        }
        printf("\n");
        i++;
    }

    return 0;
}