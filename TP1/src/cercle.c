#include <stdio.h>
#include <math.h>

int main(void) {
    double rayon = 5.0; 
    double aire = M_PI * rayon * rayon;
    double perimetre = 2 * M_PI * rayon;
    
    printf("Pour un cercle de rayon %.2f :\n", rayon);
    printf("Aire : %.5f\n", aire);
    printf("Périmètre : %.5f\n", perimetre);
    
    return 0;
}
