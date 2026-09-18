#include <stdio.h>

int main(void) {
    /* Sur un entier 32 bits numéroté de 31 (gauche / MSB) à 0 (droite / LSB) :
     * - 4e bit depuis la gauche  : indice 31 - (4 - 1)  = 28
     * - 20e bit depuis la gauche : indice 31 - (20 - 1) = 12
     */
    unsigned int d = 0x10001000; // Exemple : bits 28 et 12 positionnés à 1

    // Extraction des bits par décalage vers la droite et masquage avec le bit de poids faible
    int bit4  = (d >> 28) & 1;
    int bit20 = (d >> 12) & 1;

    // Résultat : 1 si les deux bits sont à 1, 0 sinon
    int resultat = bit4 & bit20;

    printf("%d\n", resultat);

    return 0;
}