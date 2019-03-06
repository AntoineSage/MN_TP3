#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 NRM2 :\n");

	// ---- FLOAT ----
	float af[4] = {1.0, 1.0, 1.0, 1.0};

	assert(mnblas_snrm2(3, af, 1) == 2.0);

	// ---- DOUBLE ----
	double ad[4] = {1.0, 1.0, 1.0, 1.0};

	assert(mnblas_dnrm2(3, af, 1) == 2.0);

	// ---- COMPLEXE FLOAT ----


	// ---- COMPLEXE DOUBLE ----

	printf("OK\n");
}
