#include <limits.h>

#include "operator.h"

int somme(int num1, int num2)
{
	return num1 + num2;
}

int difference(int num1, int num2)
{
	return num1 - num2;
}

int produit(int num1, int num2)
{
	return num1 * num2;
}

int quotient(int num1, int num2)
{
	return num1 / num2;
}

int modulo(int num1, int num2)
{
	return num1 % num2;
}

int et_binaire(int num1, int num2)
{
	return num1 & num2;
}

int ou_binaire(int num1, int num2)
{
	return num1 | num2;
}

int negation(int num1, int num2)
{
	(void)num2;
	return ~num1;
}

int executer_operation(int num1, int num2, char operateur, int *resultat)
{
	switch (operateur) {
	case '+':
		*resultat = somme(num1, num2);
		break;
	case '-':
		*resultat = difference(num1, num2);
		break;
	case '*':
		*resultat = produit(num1, num2);
		break;
	case '/':
		if (num2 == 0 || (num1 == INT_MIN && num2 == -1)) {
			return 0;
		}
		*resultat = quotient(num1, num2);
		break;
	case '%':
		if (num2 == 0 || (num1 == INT_MIN && num2 == -1)) {
			return 0;
		}
		*resultat = modulo(num1, num2);
		break;
	case '&':
		*resultat = et_binaire(num1, num2);
		break;
	case '|':
		*resultat = ou_binaire(num1, num2);
		break;
	case '~':
		*resultat = negation(num1, num2);
		break;
	default:
		return 0;
	}

	return 1;
}
