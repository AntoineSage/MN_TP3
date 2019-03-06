#include <assert.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 AXPY :\n");

	float a[5] = {1.0, 2.0, 3.0, 4.0,5.0};
	float b[4];

	cblas_saxpy (4, 3, a, 1, b, 1);

	int i;
	for (i = 0; i < 4; i++) {
		assert(a[i] == 3*b[i]);
	}

	printf("OK REEL\n");

    float a[5] = {1.0, 2.0, 3.0, 4.0,5.0};
	float b[4];

	cblas_saxpy (4, 3, a, 1, b, 1);

	int i;
	for (i = 0; i < 4; i++) {
		assert(a[i] == 3*b[i]);
	}

	printf("OK REEL\n");

}