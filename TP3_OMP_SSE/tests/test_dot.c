#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

void test_float() {
	float af[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	float bf[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

	float res = mncblas_sdot(5, af, 1, bf, 1);

	float res_th = 0.0;
	for (int i = 0; i < 5; i++) {
		res_th += af[i] * bf[i];
	}

	assert(res == res_th);
}

void test_double() {
	double af[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
	double bf[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

	double res = mncblas_ddot(5, af, 1, bf, 1);

	double res_th = 0.0;
	for (int i = 0; i < 5; i++) {
		res_th += af[i] * bf[i];
	}

	assert(res == res_th);
}

void test_c_float() {
	complexe_float_t afc[5];
	complexe_float_t bfc[5];
	for (int i = 0; i < 5; i++) {
		afc[i].imaginary = i;
		afc[i].real = i;
		bfc[i].imaginary = i;
		bfc[i].real = i;
	}

	complexe_float_t res;
	mncblas_cdotu(5, afc, 1, bfc, 1, &res);

	complexe_float_t res_th;
	res_th.imaginary = 0.0;
	res_th.real = 0.0;
	for (int i = 0; i < 5; i++) {
		res_th = add_complexe_float(res_th, mult_complexe_float(((complexe_float_t *)afc)[i],
																((complexe_float_t *)bfc)[i]));
	}

	assert(complexe_equal_float(res, res_th));
}

void test_c_double() {
	complexe_double_t afc[5];
	complexe_double_t bfc[5];
	for (int i = 0; i < 5; i++) {
		afc[i].imaginary = i;
		afc[i].real = i;
		bfc[i].imaginary = i;
		bfc[i].real = i;
	}

	complexe_double_t res;
	mncblas_zdotu(5, afc, 1, bfc, 1, &res);

	complexe_double_t res_th;
	res_th.imaginary = 0.0;
	res_th.real = 0.0;
	for (int i = 0; i < 5; i++) {
		res_th = add_complexe_double(res_th, mult_complexe_double(((complexe_double_t *)afc)[i],
																  ((complexe_double_t *)bfc)[i]));
	}

	assert(complexe_equal_double(res, res_th));
}

int main(int argc, char const *argv[]) {
	printf("TEST DES FONCTIONS BLAS1 DOT :\n");

	test_float();
	test_double();
	test_c_float();
	test_c_double();

	printf("OK\n");
}
