#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

complexe_float_t init_comp_float(float a, float b) {
	complexe_float_t c;
	c.real = a;
	c.imaginary = b;
	return c;
}

void test_float() {
	float A[4] = {1, 2, 3, 4};
	float X[2] = {1, 2};
	float Y[2] = {3, 4};

	mncblas_sgemv(MNCblasRowMajor, MNCblasNoTrans, 2, 2, 5, A, 0, X, 1, 6, Y, 1);
	assert(Y[0] == 43);
	assert(Y[1] == 79);
}

void test_complexe_float() {
	complexe_float_t A[4];
	complexe_float_t X[2];
	complexe_float_t Y[2];

	for (int i = 0; i < 4; i++) {
		A[i] = init_comp_float((float)i + 1.0, (float)i + 1.0);
	}

	for (int i = 0; i < 2; i++) {
		X[i] = init_comp_float((float)i + 1.0, (float)i + 1.0);
	}

	for (int i = 0; i < 2; i++) {
		Y[i] = init_comp_float(3.0 + (float)i, 3.0 + (float)i);
	}

	complexe_float_t c1 = init_comp_float(5.0, 5.0);
	complexe_float_t c2 = init_comp_float(6.0, 6.0);

	mncblas_cgemv(MNCblasRowMajor, MNCblasNoTrans, 2, 2, &c1, A, 0, X, 1, &c2, Y, 1);
}

int main() {
	printf("TEST DES FONCTIONS BLAS2 GEMV :\n");

	test_float();
	printf("FLOAT OK\n");
	test_complexe_float();
	printf("COMPLEXE FLOAT OK\n");

	return 0;
}