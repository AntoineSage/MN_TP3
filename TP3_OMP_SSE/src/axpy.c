#include <stdio.h>
#include "complexe.h"
#include "mnblas.h"


void mncblas_saxpy(const int N, const float a, const float *X, const int incX, float *Y,
				   const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		Y[j] += a * X[i];
	}
}

void mncblas_daxpy(const int N, const double a, const double *X, const int incX, double *Y,
				   const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		Y[j] += a * X[i];
	}
}

void mncblas_caxpy(const int N, const void *a, const void *X, const int incX, void *Y,
				   const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	complexe_float_t ac = *(complexe_float_t *)a;
	
	for (; ((i < N) && (j < N)); i += incX, j += incY) {

		((complexe_float_t *)Y)[j] = add_complexe_float(
			mult_complexe_float(((complexe_float_t *)X)[i], ac),
			((complexe_float_t *)Y)[j]);
	}
}

void mncblas_zaxpy(const int N, const void *a, const void *X, const int incX, void *Y,
				   const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	complexe_double_t ac = *(complexe_double_t *)a;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		((complexe_double_t *)Y)[j] = add_complexe_double(
			mult_complexe_double(((complexe_double_t *)X)[i], ac),
			((complexe_double_t *)Y)[j]);
	}
}
