#include <assert.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 COPY :\n");

	float a[5] = {1.0, 2.0, 3.0, 4.0};
	float b[5];

	mncblas_scopy(5, a, 1, b, 1);

	int i;
	for (i = 0; i < 5; i++) {
		assert(a[i] == b[i]);
	}

	printf("OK\n");
}
