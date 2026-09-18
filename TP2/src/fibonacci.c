#include <stdio.h>

int main(void) {
    int n = 7;

    if (n < 0) {
        printf("Erreur : n doit être supérieur ou égal à 0.\n");
        return 1;
    }

    long long u0 = 0;
    long long u1 = 1;

    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf("%lld", u0);
        } else if (i == 1) {
            printf(", %lld", u1);
        } else {
            long long un = u0 + u1;
            printf(", %lld", un);
            u0 = u1;
            u1 = un;
        }
    }
    printf("\n");

    return 0;
}