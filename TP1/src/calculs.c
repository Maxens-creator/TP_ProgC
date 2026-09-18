
#include <stdio.h>

int main(void) {
    int num1 = 12;
    int num2 = 4;
    char op = '&'; // Testez avec '+', '-', '*', '/', '%', '&', '|', '~'

    switch (op) {
        case '+':
            printf("%d + %d = %d\n", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%d - %d = %d\n", num1, num2, num1 - num2);
            break;
        case '*':
            printf("%d * %d = %d\n", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 == 0) {
                printf("Erreur : division par zéro impossible.\n");
            } else {
                printf("%d / %d = %d\n", num1, num2, num1 / num2);
            }
            break;
        case '%':
            if (num2 == 0) {
                printf("Erreur : modulo par zéro impossible.\n");
            } else {
                printf("%d %% %d = %d\n", num1, num2, num1 % num2);
            }
            break;
        case '&':
            printf("%d & %d = %d\n", num1, num2, num1 & num2);
            break;
        case '|':
            printf("%d | %d = %d\n", num1, num2, num1 | num2);
            break;
        case '~':
            // L'opérateur de complément binaire (NOT) est unaire : il ne s'applique qu'à une seule opérande
            printf("~%d = %d\n", num1, ~num1);
            printf("~%d = %d\n", num2, ~num2);
            break;
        default:
            printf("Opérateur inconnu : %c\n", op);
            break;
    }

    return 0;
}