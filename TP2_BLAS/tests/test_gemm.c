#include <assert.h>
#include <complexe.h>
#include <mnblas.h>
#include <stdio.h>

void test_float_1() {
	// ---- FLOAT ----
	float A[6] = {1, 4, 2, 5, 3, 6};
	float B[6] = {7, 8, 9, 10, 11, 12};
	float C[9] = {13, 14, 15, 16, 17, 18, 19, 20, 21};

	mncblas_sgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, 3, 3, 2, 0.5, A, 0, B, 0, 2.0, C,
				  0);

	printf("{ \n");
	for (int i = 0; i < 9; i++) {
		printf("%f ", C[i]);
	}
	printf("}\n");
}

void test_float_2() {
	// ---- FLOAT ----
	float A[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	float B[6] = {9, 10, 11, 12, 13, 14};
	float C[12] = {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

	mncblas_sgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, 4, 3, 2, -1.0, A, 0, B, 0, 0.3,
				  C, 0);

	printf("{ \n");
	for (int i = 0; i < 12; i++) {
		printf("%f ", C[i]);
	}
	printf("}\n");
}

int main(int argc, char const* argv[]) {
	printf("TEST DES FONCTIONS BLAS3 GEMM :\n");

	test_float_1();
	test_float_2();

	printf("OK\n");
}
