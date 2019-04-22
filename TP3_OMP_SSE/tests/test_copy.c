#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

void test_float() {
	float af[16] __attribute__((aligned(32))) = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0,
												 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0};
	float bf[16] __attribute__((aligned(32)));
	;

	mncblas_scopy(16, af, 1, bf, 1);

	for (int i = 0; i < 16; i++) {
		assert(af[i] == bf[i]);
	}
}

void test_float_V() {
	float af[16] __attribute__((aligned(32))) = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0,
												 4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0};
	float bf[16] __attribute__((aligned(32)));
	;

	mncblas_scopy_V(16, af, 1, bf, 1);

	for (int i = 0; i < 16; i++) {
		assert(af[i] == bf[i]);
	}
}

void test_double() {
	double ad[16] __attribute__((aligned(32))) = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0,
												  4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0};
	double bd[16] __attribute__((aligned(32)));
	;

	mncblas_dcopy(16, ad, 1, bd, 1);

	for (int i = 0; i < 16; i++) {
		assert(ad[i] == bd[i]);
	}
}

void test_double_V() {
	double ad[16] __attribute__((aligned(32))) = {1.0, 2.0, 3.0, 4.0, 5.0, 1.0, 2.0, 3.0,
												  4.0, 5.0, 1.0, 2.0, 3.0, 4.0, 5.0, 1.0};
	double bd[16] __attribute__((aligned(32)));
	;

	mncblas_dcopy_V(16, ad, 1, bd, 1);

	for (int i = 0; i < 16; i++) {
		assert(ad[i] == bd[i]);
	}
}

void test_complex() {
	complexe_float_t afc[16];
	complexe_float_t bfc[16];
	for (int i = 0; i < 16; i++) {
		afc[i].imaginary = i;
		afc[i].real = i;
	}

	mncblas_ccopy(16, afc, 1, bfc, 1);

	for (int i = 0; i < 16; i++) {
		assert(complexe_equal_float(afc[i], bfc[i]));
	}
}

void test_complex_V() {
	complexe_float_t afc[16] __attribute__((aligned(32)));
	complexe_float_t bfc[16] __attribute__((aligned(32)));
	for (int i = 0; i < 16; i++) {
		afc[i].imaginary = i;
		afc[i].real = i;
	}

	mncblas_ccopy_V(16, afc, 1, bfc, 1);

	for (int i = 0; i < 16; i++) {
		assert(complexe_equal_float(afc[i], bfc[i]));
	}
}

void test_complex_double() {
	complexe_double_t adc[16];
	complexe_double_t bdc[16];
	for (int i = 0; i < 16; i++) {
		adc[i].imaginary = i;
		adc[i].real = i;
	}

	mncblas_zcopy(16, adc, 1, bdc, 1);

	for (int i = 0; i < 16; i++) {
		assert(complexe_equal_double(adc[i], bdc[i]));
	}
}

void test_complex_double_V() {
	complexe_double_t adc[16] __attribute__((aligned(32)));
	complexe_double_t bdc[16] __attribute__((aligned(32)));
	for (int i = 0; i < 16; i++) {
		adc[i].imaginary = i;
		adc[i].real = i;
	}

	mncblas_zcopy_V(16, adc, 1, bdc, 1);

	for (int i = 0; i < 16; i++) {
		assert(complexe_equal_double(adc[i], bdc[i]));
	}
}

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 COPY :\n");

	test_float();
	test_float_V();
	test_double();
	test_double_V();
	test_complex();
	test_complex_V();
	test_complex_double();
	test_complex_double_V();

	printf("OK\n");
}
