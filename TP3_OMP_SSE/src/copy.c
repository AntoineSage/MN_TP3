#include <complexe.h>
#include <immintrin.h>
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

void mncblas_scopy_V(const int N, const float *X, const int incX, float *Y, const int incY) {
	register unsigned int i;

	for (i = 0; i < N; i += (256 / (sizeof(float) * 8))) {
		__m256 val = _mm256_load_ps(&(X[i]));
		_mm256_store_ps(&(Y[i]), val);
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

void mncblas_dcopy_V(const int N, const double *X, const int incX, double *Y, const int incY) {
	register unsigned int i;

	for (i = 0; i < N; i += (256 / (sizeof(double) * 8))) {
		__m256d val = _mm256_load_pd(&(X[i]));
		_mm256_store_pd(&(Y[i]), val);
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

void mncblas_ccopy_V(const int N, const void *X, const int incX, void *Y, const int incY) {
	register const complexe_float_t *X_cast = (const complexe_float_t *)X;
	register complexe_float_t *Y_cast = (complexe_float_t *)Y;

	register unsigned int i;

	for (i = 0; i < N;
		 i += (256 / (sizeof(float) * 8)) / (sizeof(complexe_float_t) / sizeof(float))) {
		__m256 val = _mm256_load_ps((const float *)(&(X_cast)[i]));
		_mm256_store_ps((float *)(&(Y_cast[i])), val);
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

void mncblas_zcopy_V(const int N, const void *X, const int incX, void *Y, const int incY) {
	register const complexe_double_t *X_cast = (const complexe_double_t *)X;
	register complexe_double_t *Y_cast = (complexe_double_t *)Y;

	register unsigned int i;

	for (i = 0; i < N;
		 i += (256 / (sizeof(double) * 8)) / (sizeof(complexe_double_t) / sizeof(double))) {
		__m256d val = _mm256_load_pd((const double *)&(X_cast)[i]);
		_mm256_store_pd((double *)&(Y_cast[i]), val);
	}

	return;
}
