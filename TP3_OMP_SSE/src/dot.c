#include <complexe.h>
#include <mnblas.h>

float mncblas_sdot(const int N, const float *X, const int incX, const float *Y, const int incY) {
	register unsigned int i;
	register float dot = 0.0;

#pragma omp parallel for schedule(static) reduction(+ : dot)
	for (i = 0; i < N; i += incX) {
		dot = dot + X[i] * Y[i];
	}

	return dot;
}

double mncblas_ddot(const int N, const double *X, const int incX, const double *Y, const int incY) {
	register unsigned int i;
	register float dot = 0.0;

#pragma omp parallel for schedule(static) reduction(+ : dot)
	for (i = 0; i < N; i += incX) {
		dot = dot + X[i] * Y[i];
	}

	return dot;
}

void mncblas_cdotu(const int N, const void *X, const int incX, const void *Y, const int incY,
				   void *dotu) {
	register unsigned int i = 0;

	float dot_real = 0.0;
	float dot_imaginary = 0.0;


#pragma omp parallel for schedule(static) reduction(+ : dot_real, dot_imaginary)
	for (i = 0; i < N; i += incX) {
		complexe_float_t res =
			mult_complexe_float(((complexe_float_t *)X)[i], ((complexe_float_t *)Y)[i]);
		dot_real += res.real;
		dot_imaginary += res.imaginary;
	}
	complexe_float_t *dot = ((complexe_float_t *)dotu);
	dot->imaginary = dot_imaginary;
	dot->real = dot_real;
}

void mncblas_cdotc(const int N, const void *X, const int incX, const void *Y, const int incY,
				   void *dotc) {
	register unsigned int i = 0;

	float dot_real = 0.0;
	float dot_imaginary = 0.0;

#pragma omp parallel for schedule(static) reduction(+ : dot_real, dot_imaginary)
	for (i = 0; i < N; i += incX) {
		complexe_float_t res =
			mult_complexe_conjug_float(((complexe_float_t *)X)[i], ((complexe_float_t *)Y)[i]);

		dot_real += res.real;
		dot_imaginary += res.imaginary;
	}
	complexe_float_t *dot = ((complexe_float_t *)dotc);

	dot->imaginary = 0.0;
	dot->real = 0.0;
}

void mncblas_zdotu(const int N, const void *X, const int incX, const void *Y, const int incY,
				   void *dotu) {
	register unsigned int i = 0;

	double dot_real = 0.0;
	double dot_imaginary = 0.0;


#pragma omp parallel for schedule(static) reduction(+ : dot_real, dot_imaginary)
	for (i = 0; i < N; i += incX) {
		complexe_double_t res =
			mult_complexe_double(((complexe_double_t *)X)[i], ((complexe_double_t *)Y)[i]);
		dot_real += res.real;
		dot_imaginary += res.imaginary;
	}
	complexe_double_t *dot = ((complexe_double_t *)dotu);
	dot->imaginary = dot_imaginary;
	dot->real = dot_real;
}

void mncblas_zdotc(const int N, const void *X, const int incX, const void *Y, const int incY,
				   void *dotc) {
	register unsigned int i = 0;

	double dot_real = 0.0;
	double dot_imaginary = 0.0;

#pragma omp parallel for schedule(static) reduction(+ : dot_real, dot_imaginary)
	for (i = 0; i < N; i += incX) {
		complexe_double_t res =
			mult_complexe_conjug_double(((complexe_double_t *)X)[i], ((complexe_double_t *)Y)[i]);

		dot_real += res.real;
		dot_imaginary += res.imaginary;
	}
	complexe_double_t *dot = ((complexe_double_t *)dotc);

	dot->imaginary = 0.0;
	dot->real = 0.0;
}
