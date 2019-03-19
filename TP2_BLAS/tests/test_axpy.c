#include <assert.h>
#include <mnblas.h>
#include "complexe.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 AXPY :\n");

	float a[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float b[4] = {2.0, 4.0, 1.0, 6.0};

	mncblas_saxpy(4, 3, a, 1, b, 1);

	assert(b[0] == 5.0);
	assert(b[1] == 10.0);
	assert(b[2] == 10.0);
	assert(b[3] == 18.0);

	printf("OK REEL\n");

	complexe_double_t ac[2];
	complexe_double_t bc[2];

	ac[0].real=1.0;
	ac[0].imaginary=2.0;
	ac[1].real=3.0;
	ac[1].imaginary=3.0;

	bc[0].real=2.0;
	bc[0].imaginary=2.0;
	bc[1].real=4.0;
	bc[1].imaginary=4.0;

	complexe_double_t cc[1];
	cc[0].real=2.0;
	cc[0].imaginary=2.0;

	mncblas_caxpy(2, cc, ac, 1, bc, 1);

	printf("ffff: %f\n",bc[0].real);

	assert(bc[0].real==0.0);
	assert(bc[0].imaginary==6.0);

	

}