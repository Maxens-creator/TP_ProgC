#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int a = 16;
    int b = 3;

    /* Opérateurs arithmétiques */
    printf("Addition (a + b) : %d\n", a + b);
    printf("Soustraction (a - b) : %d\n", a - b);
    printf("Multiplication (a * b) : %d\n", a * b);
    printf("Division entière (a / b) : %d\n", a / b);
    printf("Modulo (a %% b) : %d\n\n", a % b);

    /* Opérateurs de comparaison / logiques */
    bool est_egal = (a == b);
    bool est_superieur = (a > b);

    printf("a == b : %s (%d)\n", est_egal ? "true" : "false", est_egal);
    printf("a > b  : %s (%d)\n", est_superieur ? "true" : "false", est_superieur);

    return 0;
}