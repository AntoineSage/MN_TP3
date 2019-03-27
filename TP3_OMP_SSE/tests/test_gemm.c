#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

complexe_float_t set_complex_float(float real, float imaginary) {
	complexe_float_t c;
	c.real = real;
	c.imaginary = imaginary;

	return c;
}

int array_equal_float(float* A, float* B, int size) {
	for (int i = 0; i < size; i++) {
		if (A[i] != B[i]) {
			return 0;
		}
	}
	return 1;
}

int array_equal_complex_float(complexe_float_t* A, complexe_float_t* B, int size) {
	for (int i = 0; i < size; i++) {
		if (!complexe_equal_float(A[i], B[i])) {
			printf("%d A(%f, %f i) B(%f, %f i)\n", i, A[i].real, A[i].imaginary, B[i].real,
				   B[i].imaginary);
			return 0;
		}
	}
	return 1;
}

// (2.5) * {{1 + i, 2 + 2*i}, {3 + 3*i, 4 + 4*i}} * {{5 + 5 *i, 6 + 6*i, 7 + 7*i}, {8 + 8*i, 9 +
// 9*i, 10 + 10 *i}} - (2 + i)*{{11 + 11*i, 12 + 12*i, 13 + 13*i},{14 + 14*i, 15+15*i,16 + 16*i}}

// -11 + 72i, -12 + 84i, -13 + 96i
// -14 + 193i, -15 + 225i, -16 + 257i

void test_complex() {
	complexe_float_t A[4];
	for (int i = 0; i < 4; i++) {
		A[i].real = i + 1;
		A[i].imaginary = i + 1;
	}
	complexe_float_t B[6];
	for (int i = 0; i < 6; i++) {
		B[i].real = i + 5;
		B[i].imaginary = i + 5;
	}
	complexe_float_t C[6];
	for (int i = 0; i < 6; i++) {
		C[i].real = i + 11;
		C[i].imaginary = i + 11;
	}
	complexe_float_t Result[6];
	Result[0] = set_complex_float(-11.0, 72.0);
	Result[1] = set_complex_float(-12.0, 84.0);
	Result[2] = set_complex_float(-13.0, 96.0);
	Result[3] = set_complex_float(-14.0, 193.0);
	Result[4] = set_complex_float(-15.0, 225.0);
	Result[5] = set_complex_float(-16.0, 257.0);

	complexe_float_t alpha;
	alpha.imaginary = 0.0;
	alpha.real = 2.5;
	complexe_float_t beta;
	beta.real = -2;
	beta.imaginary = -1;

	mncblas_cgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, 2, 3, 2, &alpha, A, 0, B, 0,
				  &beta, C, 0);

	assert(array_equal_complex_float(C, Result, 6));
}

void test_float_1() {
	float A[6] = {1, 4, 2, 5, 3, 6};
	float B[6] = {7, 8, 9, 10, 11, 12};
	float C[9] = {13, 14, 15, 16, 17, 18, 19, 20, 21};
	float Result[9] = {49.5, 54, 58.5, 64, 69.5, 75, 78.5, 85, 91.5};

	mncblas_sgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, 3, 3, 2, 0.5, A, 0, B, 0, 2.0, C,
				  0);

	assert(array_equal_float(C, Result, 9));
}

void test_float_2() {
	float A[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	float B[6] = {9, 10, 11, 12, 13, 14};
	float C[12] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
	float Result[12] = {4.5, 6, 7.5, 58.5, 66, 73.5, 112.5, 126, 139.5, 166.5, 186, 205.5};

	mncblas_sgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, 4, 3, 2, 1.5, A, 0, B, 0, -3, C,
				  0);

	assert(array_equal_float(C, Result, 12));
}

int main(int argc, char const* argv[]) {
	printf("TEST DES FONCTIONS BLAS3 GEMM :\n");

	test_float_1();
	test_float_2();
	test_complex();

	printf("OK\n");
}
