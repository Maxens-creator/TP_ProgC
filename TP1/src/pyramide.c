
#include <stdio.h>

int main(void) {
    int n = 5;
    int i, j;

    for (i = 1; i <= n; i++) {
        // 1. Espaces pour aligner et centrer la pyramide
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // 2. Nombres croissants de 1 jusqu'à i
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        // 3. Nombres décroissants de i - 1 jusqu'à 1
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        // Passage à la ligne suivante
        printf("\n");
    }

    printf("\nGénération de la pyramide terminée.\n");

    return 0;
}