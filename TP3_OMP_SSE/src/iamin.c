#include <complexe.h>
#include <math.h>
#include <mnblas.h>

CBLAS_INDEX mnblas_isamin(const int N, const float *X, const int incX) {
	if (N < 0 || incX < 0) return 0;

	register unsigned int i = 1;
	register unsigned int min_index = 0;

	for (; i < N; i += incX) {
		if (abs(X[i]) < abs(X[min_index])) {
			min_index = i;
		}
	}

	return min_index;
}

CBLAS_INDEX mnblas_idamin(const int N, const double *X, const int incX) {
	if (N < 0 || incX < 0) return 0;

	register unsigned int i = 1;
	register unsigned int min_index = 0;

	for (; i < N; i += incX) {
		if (abs(X[i]) < abs(X[min_index])) {
			min_index = i;
		}
	}

	return min_index;
}

CBLAS_INDEX mnblas_icamin(const int N, const void *X, const int incX) {
	if (N < 0 || incX < 0) return 0;

	register unsigned int i = 1;
	register unsigned int min_index = 0;
	register float min =
		abs(((complexe_float_t *)X)[0].imaginary) + abs(((complexe_float_t *)X)[0].real);

	for (; i < N; i += incX) {
		register float x_i =
			abs(((complexe_float_t *)X)[i].imaginary) + abs(((complexe_float_t *)X)[i].real);

		if (x_i < min) {
			min_index = i;
			min = x_i;
		}
	}

	return min_index;
}

CBLAS_INDEX mnblas_izamin(const int N, const void *X, const int incX) {
	if (N < 0 || incX < 0) return 0;

	register unsigned int i = 1;
	register unsigned int min_index = 0;
	register double min =
		abs(((complexe_double_t *)X)[0].imaginary) + abs(((complexe_double_t *)X)[0].real);

	for (; i < N; i += incX) {
		register double x_i =
			abs(((complexe_double_t *)X)[i].imaginary) + abs(((complexe_double_t *)X)[i].real);

		if (x_i < min) {
			min_index = i;
			min = x_i;
		}
	}

	return min_index;
}