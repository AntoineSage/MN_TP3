#include "complexe.h"
#include "math.h"
#include "mnblas.h"


void cblas_sgemv (const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE trans, const MKL_INT m, const MKL_INT n,
 const float alpha, const float *a, const MKL_INT lda, const float *x, const MKL_INT incx, const float beta, float *y, const MKL_INT incy){

     

 }



float mncblas_scasum(const int n, const void *X, const int incX) {
	register unsigned int i = 0;
	register float sum = 0;

	for (; (i < n); i += incX) {
		sum =
			sum + abs(((complexe_float_t *)X)[i].real) + abs(((complexe_float_t *)X)[i].imaginary);
	}

	return sum;
}


double mncblas_dasum(const int n, const double *X, const int incX) {
	register unsigned int i = 0;
	register double sum = 0;

	for (; (i < n); i += incX) {
		sum = sum + abs(X[i]);
	}

	return sum;
}

double mncblas_dzasum(const int n, const void *X, const int incX) {
	register unsigned int i = 0;
	register double sum = 0;

	for (; (i < n); i += incX) {
		sum = sum + abs(((complexe_double_t *)X)[i].real) +
			  abs(((complexe_double_t *)X)[i].imaginary);
	}

	return sum;
}
