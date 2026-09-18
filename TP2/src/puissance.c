#include <stdio.h>

int main(void) {
    int a = 2;
    int b = 3;
    long long resultat = 1;

    // Calcul de a^b pour b >= 0
    for (int i = 0; i < b; i++) {
        resultat *= a;
    }

    printf("%d élevé à la puissance %d = %lld\n", a, b, resultat);

    return 0;
}