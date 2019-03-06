#include <complexe.h>
#include <mnblas.h>

float mncblas_sdot(const int N, const float *X, const int incX, const float *Y, const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;
	register float dot = 0.0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		dot = dot + X[i] * Y[j];
	}

	return dot;
}

double mncblas_ddot(const int N, const double *X, const int incX, const double *Y, const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;
	register float dot = 0.0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		dot = dot + X[i] * Y[j];
	}

	return dot;
}

void mncblas_cdotu_sub(const int N, const void *X, const int incX, const void *Y, const int incY,
					   void *dotu) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	complexe_float_t *dot = ((complexe_float_t *)dotu);

	dot->imaginary = 0.0;
	dot->real = 0.0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		*dot = add_complexe_float(
			*dot, mult_complexe_float(((complexe_float_t *)X)[i], ((complexe_float_t *)Y)[j]));
	}
}

void mncblas_cdotc_sub(const int N, const void *X, const int incX, const void *Y, const int incY,
					   void *dotc) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	complexe_float_t *dot = ((complexe_float_t *)dotc);

	dot->imaginary = 0.0;
	dot->real = 0.0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		*dot = add_complexe_float(*dot, mult_complexe_conjug_float(((complexe_float_t *)X)[i],
																   ((complexe_float_t *)Y)[j]));
	}
}

void mncblas_zdotu_sub(const int N, const void *X, const int incX, const void *Y, const int incY,
					   void *dotu) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	complexe_double_t *dot = ((complexe_double_t *)dotu);

	dot->imaginary = 0.0;
	dot->real = 0.0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		*dot = add_complexe_double(
			*dot, mult_complexe_double(((complexe_double_t *)X)[i], ((complexe_double_t *)Y)[j]));
	}
}

void mncblas_zdotc_sub(const int N, const void *X, const int incX, const void *Y, const int incY,
					   void *dotc) {
	register unsigned int i = 0;
	register unsigned int j = 0;

	complexe_double_t *dot = ((complexe_double_t *)dotc);

	dot->imaginary = 0.0;
	dot->real = 0.0;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		*dot = add_complexe_double(*dot, mult_complexe_conjug_double(((complexe_double_t *)X)[i],
																	 ((complexe_double_t *)Y)[j]));
	}
}
