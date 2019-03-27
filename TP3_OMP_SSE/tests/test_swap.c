#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 SWAP :\n");

	// ---- FLOAT ----
	float af[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float bf[5] = {5.0, 4.0, 3.0, 2.0, 1.0};

	mncblas_sswap(5, af, 1, bf, 1);

	int i;
	for (i = 0; i < 5; i++) {
		assert(af[i] == 5 - i);
		assert(bf[i] == i + 1);
	}

	// ---- DOUBLE ----
	double ad[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double bd[5] = {5.0, 4.0, 3.0, 2.0, 1.0};

	mncblas_dswap(5, ad, 1, bd, 1);

	for (i = 0; i < 5; i++) {
		assert(af[i] == 5 - i);
		assert(bf[i] == i + 1);
	}

	// ---- COMPLEXE FLOAT ----
	complexe_float_t afc[5];
	complexe_float_t bfc[5];
	for (i = 0; i < 5; i++) {
		afc[i].imaginary = 1.0;
		afc[i].real = 1.0;

		bfc[i].imaginary = 2.0;
		bfc[i].real = 2.0;
	}

	mncblas_cswap(5, afc, 1, bfc, 1);

	for (i = 0; i < 5; i++) {
		assert(afc[i].imaginary == 2.0);
		assert(afc[i].real == 2.0);
		assert(bfc[i].imaginary == 1.0);
		assert(bfc[i].real == 1.0);
	}

	// ---- COMPLEXE DOUBLE ----
	complexe_double_t adc[5];
	complexe_double_t bdc[5];
	for (i = 0; i < 5; i++) {
		adc[i].imaginary = 1.0;
		adc[i].real = 1.0;

		bdc[i].imaginary = 2.0;
		bdc[i].real = 2.0;
	}

	mncblas_zswap(5, adc, 1, bdc, 1);

	for (i = 0; i < 5; i++) {
		assert(adc[i].imaginary == 2.0);
		assert(adc[i].real == 2.0);
		assert(bdc[i].imaginary == 1.0);
		assert(bdc[i].real == 1.0);
	}

	printf("OK\n");
}
