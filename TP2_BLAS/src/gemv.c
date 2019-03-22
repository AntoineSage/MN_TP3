#include "complexe.h"
#include "math.h"
#include "mnblas.h"


void mncblas_sgemv(const MNCBLAS_LAYOUT layout, const MNCBLAS_TRANSPOSE TransA, const int M, const int N, const float alpha, const float *A, 
const int lda, const float *X, const int incX, const float beta, float *Y, const int incY){
    
    // Cas où il n'y a rien à faire
	if (M == 0 || N == 0 || (alpha == 0 && beta == 1)) return;

	// Beta = 0 -> des 0 partout dans le vecteur Y
	if (beta == 0) {
		register unsigned int i = 0;
		for (; i < M; i++) {
			Y[i] = 0.0;
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
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
			for (; j < N; j++) {
				float calcul = alpha*A[i*N+j]*X[j*incX];
				Y[i] += calcul;
			}
		}
	}

 }


void mncblas_dgemv(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, const int M, const int N,
				   const double alpha, const double *A, const int lda, const double *X,
				   const int incX, const double beta, double *Y, const int incY){
    
    // Cas où il n'y a rien à faire
	if (M == 0 || N == 0 || (alpha == 0 && beta == 1)) return;

	// Beta = 0 -> des 0 partout dans le vecteur Y
	if (beta == 0) {
		register unsigned int i = 0;
		for (; i < M; i++) {
			Y[i] = 0.0;
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
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
			for (; j < N; j++) {
				float calcul = alpha*A[i*N+j]*X[j*incX];
				Y[i] += calcul;
			}
		}
	}

 }

	

void mncblas_cgemv(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, const int M, const int N,
				   const void *alpha, const void *A, const int lda, const void *X, const int incX,
				   const void *beta, void *Y, const int incY){
    
	complexe_float_t alphac = *(complexe_float_t *)alpha;
	complexe_float_t betac = *(complexe_float_t *)beta;

    // Cas où il n'y a rien à faire
	if (M == 0 || N == 0 || (iszero_float(alphac) && isone_float(betac))) return;

	// Beta = 0 -> des 0 partout dans le vecteur Y
	if (betac.imaginary == 0 && betac.real ==0 ){
		register unsigned int i = 0;
		for (; i < M; i++) {
			complexe_float_t zero;
			zero.imaginary=0;
			zero.real=0;
			((complexe_float_t *)Y)[i] = zero;
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			((complexe_float_t *)Y)[i] = mult_complexe_float(((complexe_float_t *)Y)[i], betac);
		}
	}

	// Alpha, rien besoin de faire de plus
	if (iszero_float(alphac)) {
		return;
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			register unsigned int j = 0;
			for (; j < N; j++) {
				complexe_float_t calcul = mult_complexe_float(alphac, mult_complexe_float(((complexe_float_t *)A)[i*N+j],((complexe_float_t *)X)[j*incX]));
				((complexe_float_t *)Y)[i] = add_complexe_float(((complexe_float_t *)Y)[i],calcul);
			}

		}
	}

 }

void mncblas_zgemv(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, const int M, const int N,
				   const void *alpha, const void *A, const int lda, const void *X, const int incX,
				   const void *beta, void *Y, const int incY){
    
	complexe_double_t alphac = *(complexe_double_t *)alpha;
	complexe_double_t betac = *(complexe_double_t *)beta;

    // Cas où il n'y a rien à faire
	if (M == 0 || N == 0 || (iszero_double(alphac) && isone_double(betac))) return;

	// Beta = 0 -> des 0 partout dans le vecteur Y
	if (betac.imaginary == 0 && betac.real ==0 ){
		register unsigned int i = 0;
		for (; i < M; i++) {
			complexe_double_t zero;
			zero.imaginary=0;
			zero.real=0;
			((complexe_double_t *)Y)[i] = zero;
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			((complexe_double_t *)Y)[i] = mult_complexe_double(((complexe_double_t *)Y)[i], betac);
		}
	}

	// Alpha, rien besoin de faire de plus
	if (iszero_double(alphac)) {
		return;
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			register unsigned int j = 0;
			for (; j < N; j++) {
				complexe_double_t calcul = mult_complexe_double(alphac, mult_complexe_double(((complexe_double_t *)A)[i*N+j],((complexe_double_t *)X)[j*incX]));
				((complexe_double_t *)Y)[i] = add_complexe_double(((complexe_double_t *)Y)[i],calcul);
			}

		}
	}

 }
