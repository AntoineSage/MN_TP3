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
		if (alpha == 0 || K == 0) {
			register unsigned int i;
#pragma omp parallel for schedule(static)
			for (i = 0; i < M * N; i++) {
				C[i] = 0.0;
			}
			return;
		} else {
			register unsigned int i;
#pragma omp parallel for schedule(static)
			for (i = 0; i < M; i++) {
				register unsigned int j = 0;
				for (; j < N; j++) {
					C[i * N + j] = (mncblas_sdot(K * N, &(A[i * K]), 1, &(B[j]), N) * alpha);
				}
			}
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i;
#pragma omp parallel for schedule(static)
		for (i = 0; i < M * N; i++) {
			C[i] *= beta;
		}
	}

	// Alpha ou K == 0, rien besoin de faire de plus
	if (alpha == 0 || K == 0) {
		return;
	} else {
		register unsigned int i;
#pragma omp parallel for schedule(static)
		for (i = 0; i < M; i++) {
			register const float *A_i = &(A[i * K]);

			register unsigned int j = 0;
			for (; j < N; j++) {
				C[i * N + j] += (mncblas_sdot(K * N, A_i, 1, &(B[j]), N) * alpha);
			}
		}
	}
}

void mncblas_dgemm(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, MNCBLAS_TRANSPOSE TransB,
				   const int M, const int N, const int K, const double alpha, const double *A,
				   const int lda, const double *B, const int ldb, const double beta, double *C,
				   const int ldc) {
	// Cas où il n'y a rien à faire
	if (M == 0 || N == 0 || ((alpha == 0 || K == 0) && beta == 1)) return;

	// Beta = 0 -> des 0 partout dans la matrice
	if (beta == 0) {
		if (alpha == 0 || K == 0) {
			register unsigned int i = 0;
			for (; i < M * N; i++) {
				C[i] = 0.0;
			}
			return;
		} else {
			register unsigned int i = 0;
			for (; i < M; i++) {
				register unsigned int j = 0;
				for (; j < N; j++) {
					C[i * N + j] = (mncblas_ddot(K * N, &(A[i * K]), 1, &(B[j]), N) * alpha);
				}
			}
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
				C[i * N + j] += (mncblas_ddot(K * N, &(A[i * K]), 1, &(B[j]), N) * alpha);
			}
		}
	}
}

void mncblas_cgemm(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, MNCBLAS_TRANSPOSE TransB,
				   const int M, const int N, const int K, const void *alpha, const void *A,
				   const int lda, const void *B, const int ldb, const void *beta, void *C,
				   const int ldc) {
	const complexe_float_t alpha_cast = *(complexe_float_t *)alpha;
	const complexe_float_t beta_cast = *(complexe_float_t *)beta;

	const complexe_float_t *A_cast = (complexe_float_t *)A;
	const complexe_float_t *B_cast = (complexe_float_t *)B;
	complexe_float_t *C_cast = (complexe_float_t *)C;

	// Cas où il n'y a rien à faire
	if (M == 0 || N == 0 ||
		(((alpha_cast.imaginary == 0 && alpha_cast.real == 0) || K == 0) &&
		 (beta_cast.real == 1 && beta_cast.imaginary == 0)))
		return;

	// Beta = 0 -> des 0 partout dans la matrice
	if (beta_cast.real == 0 && beta_cast.imaginary == 0) {
		if ((alpha_cast.real == 0 && alpha_cast.imaginary == 0) || K == 0) {
			register unsigned int i = 0;
			for (; i < M * N; i++) {
				C_cast[i].real = 0.0;
				C_cast[i].imaginary = 0.0;
			}
			return;
		} else {
			register unsigned int i = 0;
			for (; i < M; i++) {
				register unsigned int j = 0;
				for (; j < N; j++) {
					mncblas_cdotu(K * N, &(A_cast[i * K]), 1, &(B_cast[j]), N,
								  &(C_cast[i * N + j]));
					C_cast[i * N + j] = mult_complexe_float(C_cast[i * N + j], alpha_cast);
				}
			}
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < M * N; i++) {
			C_cast[i] = mult_complexe_float(C_cast[i], beta_cast);
		}
	}

	// Alpha ou K == 0, rien besoin de faire de plus
	if ((alpha_cast.imaginary == 0 && alpha_cast.real == 0) || K == 0) {
		return;
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			register unsigned int j = 0;
			for (; j < N; j++) {
				complexe_float_t tmp;
				mncblas_cdotu(K * N, &(A_cast[i * K]), 1, &(B_cast[j]), N, &(tmp));
				C_cast[i * N + j] =
					add_complexe_float(C_cast[i * N + j], mult_complexe_float(tmp, alpha_cast));
			}
		}
	}
}

void mncblas_zgemm(MNCBLAS_LAYOUT layout, MNCBLAS_TRANSPOSE TransA, MNCBLAS_TRANSPOSE TransB,
				   const int M, const int N, const int K, const void *alpha, const void *A,
				   const int lda, const void *B, const int ldb, const void *beta, void *C,
				   const int ldc) {
	const complexe_double_t alpha_cast = *(complexe_double_t *)alpha;
	const complexe_double_t beta_cast = *(complexe_double_t *)beta;

	const complexe_double_t *A_cast = (complexe_double_t *)A;
	const complexe_double_t *B_cast = (complexe_double_t *)B;
	complexe_double_t *C_cast = (complexe_double_t *)C;

	// Cas où il n'y a rien à faire
	if (M == 0 || N == 0 ||
		(((alpha_cast.imaginary == 0 && alpha_cast.real == 0) || K == 0) &&
		 (beta_cast.real == 1 && beta_cast.imaginary == 0)))
		return;

	// Beta = 0 -> des 0 partout dans la matrice
	if (beta_cast.real == 0 && beta_cast.imaginary == 0) {
		if ((alpha_cast.real == 0 && alpha_cast.imaginary == 0) || K == 0) {
			register unsigned int i = 0;
			for (; i < M * N; i++) {
				C_cast[i].real = 0.0;
				C_cast[i].imaginary = 0.0;
			}
			return;
		} else {
			register unsigned int i = 0;
			for (; i < M; i++) {
				register unsigned int j = 0;
				for (; j < N; j++) {
					mncblas_zdotu(K * N, &(A_cast[i * K]), 1, &(B_cast[j]), N,
								  &(C_cast[i * N + j]));
					C_cast[i * N + j] = mult_complexe_double(C_cast[i * N + j], alpha_cast);
				}
			}
		}
		// On multiplie chaque élément
	} else {
		register unsigned int i = 0;
		for (; i < M * N; i++) {
			C_cast[i] = mult_complexe_double(C_cast[i], beta_cast);
		}
	}

	// Alpha ou K == 0, rien besoin de faire de plus
	if ((alpha_cast.imaginary == 0 && alpha_cast.real == 0) || K == 0) {
		return;
	} else {
		register unsigned int i = 0;
		for (; i < M; i++) {
			register unsigned int j = 0;
			for (; j < N; j++) {
				mncblas_zdotu(K * N, &(A_cast[i * K]), 1, &(B_cast[j]), N, &(C_cast[i * N + j]));
				C_cast[i * N + j] = add_complexe_double(
					C_cast[i * N + j], mult_complexe_double(C_cast[i * N + j], alpha_cast));
			}
		}
	}
}