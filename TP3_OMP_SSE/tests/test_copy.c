#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 COPY :\n");

	// ---- FLOAT ----
	float af[16] __attribute__((aligned(32))) = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0,
												 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0};
	float bf[16] __attribute__((aligned(32)));
	;

	mncblas_scopy(16, af, 1, bf, 1);

	int i;
	for (i = 0; i < 16; i++) {
		assert(af[i] == bf[i]);
	}

	// ---- DOUBLE ----
	double ad[16] __attribute__((aligned(32))) = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0,
												  4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0};
	double bd[16] __attribute__((aligned(32)));
	;

	mncblas_dcopy(16, ad, 1, bd, 1);

	for (i = 0; i < 16; i++) {
		assert(ad[i] == bd[i]);
	}

	// ---- COMPLEXE FLOAT ----
	complexe_float_t afc[5];
	complexe_float_t bfc[5];
	for (i = 0; i < 5; i++) {
		afc[i].imaginary = i;
		afc[i].real = i;
	}

	mncblas_ccopy(4, afc, 1, bfc, 1);

	for (i = 0; i < 4; i++) {
		assert(complexe_equal_float(afc[i], bfc[i]));
	}
	bfc[4].imaginary = 0;
	bfc[4].real = 0;
	assert(!complexe_equal_float(afc[4], bfc[4]));

	// ---- COMPLEXE DOUBLE ----
	complexe_double_t adc[5];
	complexe_double_t bdc[5];
	for (i = 0; i < 5; i++) {
		adc[i].imaginary = i;
		adc[i].real = i;
	}

	mncblas_zcopy(5, adc, 1, bdc, 1);

	for (i = 0; i < 5; i++) {
		assert(complexe_equal_double(adc[i], bdc[i]));
	}

	printf("OK\n");
}
