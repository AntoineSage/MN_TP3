#include <complexe.h>
#include <mnblas.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MINX(a, b) (((a) > (b)) ? (a) : (b))

void mncblas_scopy(const int N, const float *X, const int incX, float *Y, const int incY) {
	register unsigned int i;

#pragma omp parallel for schedule(static)
	for (i = 0; i < N; i += incX) {
		Y[i] = X[i];
	}

	return;
}

void mncblas_dcopy(const int N, const double *X, const int incX, double *Y, const int incY) {
	register unsigned int i;

#pragma omp parallel for schedule(static)
	for (i = 0; i < N; i += incX) {
		Y[i] = X[i];
	}

	return;
}

void mncblas_ccopy(const int N, const void *X, const int incX, void *Y, const int incY) {
	register unsigned int i;

#pragma omp parallel for schedule(static)
	for (i = 0; i < N; i += incX) {
		((complexe_float_t *)Y)[i] = ((complexe_float_t *)X)[i];
	}

	return;
}

void mncblas_zcopy(const int N, const void *X, const int incX, void *Y, const int incY) {
	register unsigned int i = 0;

#pragma omp parallel for schedule(static)
	for (i = 0; i < N; i += incX) {
		((complexe_double_t *)Y)[i] = ((complexe_double_t *)X)[i];
	}

	return;
}
