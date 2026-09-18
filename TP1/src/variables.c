#include <stdio.h>

int main(void) {
    char c = 'A';
    signed char sc = -65;
    unsigned char uc = 200;

    short s = -32000;
    unsigned short us = 65000;

    int i = -100000;
    unsigned int ui = 3000000000U;

    long int li = -2000000000L;
    unsigned long int uli = 4000000000UL;

    long long int lli = -9000000000000000000LL;
    unsigned long long int ulli = 18000000000000000000ULL;

    float f = 3.14f;
    double d = 2.7182818284;
    long double ld = 1.4142135623730950488L;

    printf("char : %c (valeur ASCII : %d)\n", c, c);
    printf("signed char : %d\n", sc);
    printf("unsigned char : %u\n\n", uc);

    printf("short : %d\n", s);
    printf("unsigned short : %u\n\n", us);

    printf("int : %d\n", i);
    printf("unsigned int : %u\n\n", ui);

    printf("long int : %ld\n", li);
    printf("unsigned long int : %lu\n\n", uli);

    printf("long long int : %lld\n", lli);
    printf("unsigned long long int : %llu\n\n", ulli);

    printf("float : %f\n", f);
    printf("double : %lf\n", d);
    printf("long double : %Lf\n", ld);

    return 0;
}