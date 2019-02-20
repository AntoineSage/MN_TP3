#include <stdio.h>
#include "mnblas.h"
#include "complexe.h"

complexe_float_t vecteur1[5];
complexe_float_t vecteur2[5];

for (int i=0; i<5; i++){

	vecteur1[i].real=i;
	vecteur1[i].imaginary=i;

	vecteur2[i].real=2i;
	vecteur2[i].imaginary=2i;

}

mncblas_cswap(3, vecteur1, 1, vecteur2, 1);

printf("Vecteur 1: \n");
for (i=0; i<5; i++){
	printf ("[%d + %d * i] ",vecteur1[i].real=i,vecteur1[i].imaginary=i);
}

printf("Vecteur 2: \n");
for (i=0; i<5; i++){
	printf ("[%d + %d * i] ",vecteur2[i].real=i,vecteur2[i].imaginary=i);
}
