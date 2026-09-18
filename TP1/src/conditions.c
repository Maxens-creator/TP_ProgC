#include <stdio.h>

int main(void) {
    int somme = 0;

    for (int i = 1; i <= 1000; i++) {
        // 1. Si divisible par 11, on ignore et on passe au suivant
        if (i % 11 == 0) {
            continue;
        }

        // 2. Si divisible par 5 ou par 7, on l'ajoute à somme
        if (i % 5 == 0 || i % 7 == 0) {
            somme += i;
        }

        // 3. Si la somme dépasse 5000, on interrompt immédiatement
        if (somme > 5000) {
            break;
        }
    }

    printf("Somme finale : %d\n", somme);

    return 0;
}