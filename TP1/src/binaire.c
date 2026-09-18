#include <stdio.h>

int main(void) {
    int nombres[] = {0, 4096, 65536, 65535, 1024};
    int total = sizeof(nombres) / sizeof(nombres[0]);
    int nb_bits = sizeof(int) * 8; // 32 bits sur une architecture standard

    for (int k = 0; k < total; k++) {
        int n = nombres[k];
        printf("%5d en binaire : ", n);

        int premier_un_trouve = 0;

        // Parcours du bit de poids fort (MSB) vers le bit de poids faible (LSB)
        for (int i = nb_bits - 1; i >= 0; i--) {
            int bit = (n >> i) & 1; // Décalage à droite puis masque avec l'opérateur bit à bit &

            // Détection du premier '1' pour éviter l'affichage de tous les zéros de tête
            if (bit == 1) {
                premier_un_trouve = 1;
            }

            if (premier_un_trouve) {
                printf("%d", bit);
            }
        }

        // Cas particulier où le nombre est 0
        if (!premier_un_trouve) {
            printf("0");
        }

        printf("\n");
    }

    return 0;
}