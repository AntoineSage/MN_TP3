#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const* argv[]) {
	printf("TEST DES FONCTIONS BLAS1 IAMIN et IAMAX :\n");

	// ---- FLOAT ----
	float af[4] = {1.0, 4.0, -8.0, 0.5};

	assert(mnblas_isamin(4, af, 1) == 3);
	assert(mnblas_isamax(4, af, 1) == 2);

	// ---- DOUBLE ----
	double ad[4] = {1.0, 4.0, -8.0, 0.5};

	assert(mnblas_idamin(4, ad, 1) == 3);
	assert(mnblas_idamax(4, ad, 1) == 2);

	// ---- COMPLEXE FLOAT ----
	complexe_float_t afc[3];
	afc[0].real = 10.0;
	afc[0].imaginary = -10.0;
	afc[1].real = 1.0;
	afc[1].imaginary = 1.0;
	afc[2].real = -1.0;
	afc[2].imaginary = 1.5;

	assert(mnblas_icamin(3, afc, 1) == 1);
	assert(mnblas_icamax(3, afc, 1) == 0);

	// ---- COMPLEXE DOUBLE ----

	complexe_double_t adc[3];
	adc[0].real = 10.0;
	adc[0].imaginary = -10.0;
	adc[1].real = 1.0;
	adc[1].imaginary = 1.0;
	adc[2].real = -1.0;
	adc[2].imaginary = 1.5;

	assert(mnblas_izamin(3, adc, 1) == 1);
	assert(mnblas_izamax(3, adc, 1) == 0);

	printf("OK\n");
}