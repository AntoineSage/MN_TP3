#include "complexe.h"
#include "math.h"
#include "mnblas.h"


void mncblas_sgemv(const MNCBLAS_LAYOUT layout, const MNCBLAS_TRANSPOSE TransA, const int M, const int N, const float alpha, const float *A, 
const int lda, const float *X, const int incX, const float beta, float *Y, const int incY);{
    
    // Cas où il n'y a rien à faire
	if (M == 0 || N == 0 || (alpha == 0 && beta == 1)) return;

	// Beta = 0 -> des 0 partout dans le vecteur Y
	if (beta == 0) {
		register unsigned int i = 0;
		for (; i < N; i++) {
			Y[i] = 0.0;
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < N; i++) {
			Y[i] *= beta;
		}
	}

	// Alpha, rien besoin de faire de plus
	if (alpha == 0) {
		return;
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			register unsigned int j = 0;
			for (; j < N; j += incX) {
				Y[j] += alpha*A[i*N+j]*X[j];
			}
		}
	}

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
