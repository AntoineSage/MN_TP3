#include <complexe.h>
#include <math.h>
#include <mnblas.h>

float mnblas_snrm2(const int N, const float *X, const int incX) {
	register unsigned int i = 0;
	register float nrm2 = 0.0;

	for (; (i < N); i += incX) {
		nrm2 += X[i] * X[i];
	}

	return sqrt(nrm2);
}

double mnblas_dnrm2(const int N, const double *X, const int incX) {
	register unsigned int i = 0;
	register double nrm2 = 0.0;

	for (; (i < N); i += incX) {
		nrm2 += X[i] * X[i];
	}

	return sqrt(nrm2);
}

float mnblas_scnrm2(const int N, const void *X, const int incX) {
	register unsigned int i = 0;
	register double nrm2 = 0.0;
	register complexe_float_t *X_c = (complexe_float_t *)X;

	for (; (i < N); i += incX) {
		nrm2 += module_complexe_squared_float(X_c[i]);
	}

	return sqrt(nrm2);
}

double mnblas_dznrm2(const int N, const void *X, const int incX) {
	register unsigned int i = 0;
	register double nrm2 = 0.0;
	register complexe_double_t *X_c = (complexe_double_t *)X;

	for (; (i < N); i += incX) {
		nrm2 += module_complexe_squared_double(X_c[i]);
	}

	return sqrt(nrm2);
}