#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const* argv[]) {
	printf("TEST DES FONCTIONS BLAS1 NRM2 :\n");

	// ---- FLOAT ----
	float af[4] = {1.0, 1.0, 1.0, 1.0};

	assert(mnblas_snrm2(4, af, 1) == 2.0);

	// ---- DOUBLE ----
	double ad[4] = {1.0, 1.0, 1.0, 1.0};

	assert(mnblas_dnrm2(4, ad, 1) == 2.0);

	// ---- COMPLEXE FLOAT ----
	complexe_float_t afc[2];
	afc[0].real = 1.0;
	afc[0].imaginary = 1.0;
	afc[1].real = 1.0;
	afc[1].imaginary = 1.0;

	assert(mnblas_scnrm2(2, afc, 1) == 2.0);

	// ---- COMPLEXE DOUBLE ----

	complexe_double_t adc[2];
	adc[0].real = 1.0;
	adc[0].imaginary = 1.0;
	adc[1].real = 1.0;
	adc[1].imaginary = 1.0;

	assert(mnblas_dznrm2(2, adc, 1) == 2.0);

	printf("OK\n");
}
