#include <complexe.h>
#include <mnblas.h>

// IGNORER layout, TransA, TransB, lda, ldb, ldc

void mncblas_sgemm(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, MNCBLAS_TRANSPOSE TransB,
				   const int M, const int N, const int K, const float alpha, const float *A,
				   const int lda, const float *B, const int ldb, const float beta, float *C,
				   const int ldc) {
	// Cas où il n'y a rien à faire
	if (M == 0 || N == 0 || ((alpha == 0 || K == 0) && beta == 1)) return;

	// Beta = 0 -> des 0 partout dans la matrice
	if (beta == 0) {
		register unsigned int i = 0;
		for (; i < M * N; i++) {
			C[i] = 0.0;
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < M * N; i++) {
			C[i] *= beta;
		}
	}

	// Alpha ou K == 0, rien besoin de faire de plus
	if (alpha == 0 || K == 0) {
		return;
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			register unsigned int j = 0;
			for (; j < N; j++) {
				C[i * M + j] += mncblas_sdot(K, &(A[i * M]), 1, &(B[i]), N) * alpha;
			}
		}
	}
}

void mncblas_dgemm(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, MNCBLAS_TRANSPOSE TransB,
				   const int M, const int N, const int K, const double alpha, const double *A,
				   const int lda, const double *B, const int ldb, const double beta, double *C,
				   const int ldc);

void mncblas_cgemm(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, MNCBLAS_TRANSPOSE TransB,
				   const int M, const int N, const int K, const void *alpha, const void *A,
				   const int lda, const void *B, const int ldb, const void *beta, void *C,
				   const int ldc);

void mncblas_zgemm(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, MNCBLAS_TRANSPOSE TransB,
				   const int M, const int N, const int K, const void *alpha, const void *A,
				   const int lda, const void *B, const int ldb, const void *beta, void *C,
				   const int ldc);
