#include <complexe.h>
#include <immintrin.h>
#include <mnblas.h>
#include <stdio.h>

float mncblas_sdot(const int N, const float *X, const int incX, const float *Y, const int incY) {
	register unsigned int i;
	register float dot = 0.0;

#pragma omp parallel for schedule(static) reduction(+ : dot)
	for (i = 0; i < N; i += incX) {
		dot = dot + X[i] * Y[i];
	}

	return dot;
}

float mncblas_sdot_V(const int N, const float *X, const int incX, const float *Y, const int incY) {
	register unsigned int i;
	register float dot_total = 0.0;
	float dot[4];

#pragma omp parallel for schedule(static) reduction(+ : dot_total)
	for (i = 0; i < N; i += (128 / (sizeof(float) * 8))) {
		__m128 valX = _mm_load_ps(&(X[i]));
		__m128 valY = _mm_load_ps(&(Y[i]));
		__m128 res = _mm_dp_ps(valX, valY, 0xFF);
		_mm_store_ps(dot, res);
		dot_total = dot_total + dot[0];
	}

	return dot_total;
}

double mncblas_ddot(const int N, const double *X, const int incX, const double *Y, const int incY) {
	register unsigned int i;
	register double dot = 0.0;

#pragma omp parallel for schedule(static) reduction(+ : dot)
	for (i = 0; i < N; i += incX) {
		dot = dot + X[i] * Y[i];
	}

	return dot;
}

double mncblas_ddot_V(const int N, const double *X, const int incX, const double *Y,
					  const int incY) {
	register unsigned int i;
	register double dot_total = 0.0;
	double dot[2];

#pragma omp parallel for schedule(static) reduction(+ : dot_total)
	for (i = 0; i < N; i += (128 / (sizeof(double) * 8))) {
		__m128d valX = _mm_load_pd(&(X[i]));
		__m128d valY = _mm_load_pd(&(Y[i]));
		__m128d res = _mm_dp_pd(valX, valY, 0xFF);
		_mm_store_pd(dot, res);
		dot_total = dot_total + dot[0];
	}

	return dot_total;
}

void mncblas_cdotu(const int N, const void *X, const int incX, const void *Y, const int incY,
				   void *dotu) {
	register unsigned int i = 0;
	float dot_real_total = 0.0;
	float dot_imaginary_total = 0.0;


#pragma omp parallel for schedule(static) reduction(+ : dot_real_total, dot_imaginary_total)
	for (i = 0; i < N; i += incX) {
		complexe_float_t res =
			mult_complexe_float(((complexe_float_t *)X)[i], ((complexe_float_t *)Y)[i]);
		dot_real_total += res.real;
		dot_imaginary_total += res.imaginary;
	}
	complexe_float_t *dot = ((complexe_float_t *)dotu);
	dot->imaginary = dot_imaginary_total;
	dot->real = dot_real_total;
}

// void mncblas_cdotu_V(const int N, const void *X, const int incX, const void *Y, const int incY,
// 					 void *dotu) {
// 	register unsigned int i = 0;
// 	const complexe_float_t *X_cast = (const complexe_float_t *)X;
// 	const complexe_float_t *Y_cast = (const complexe_float_t *)Y;

// 	float dot_real_total = 0.0;
// 	float dot_imaginary_total = 0.0;

// 	register __m256i addr = _mm256_set_epi32(0, 0, 0, 0, 8 * 3, 8 * 2, 8 * 1, 0);

// 	// #pragma omp parallel for schedule(static) reduction(+ : dot_real_total, dot_imaginary_total)
// 	for (i = 0; i < N; i += (256 / (sizeof(float) * 8)) / 2) {
// 		float dot_real_a[8];
// 		float dot_real_b[8];
// 		float dot_imaginary_a[8];
// 		float dot_imaginary_b[8];

// 		__m256 Xreal = _mm256_i32gather_ps((const float *)&(X_cast[i]), addr, 1);
// 		__m256 Ximaginary = _mm256_i32gather_ps(&((const float *)&(X_cast[i]))[1], addr, 1);


// 		__m256 Yreal = _mm256_i32gather_ps((const float *)&(Y_cast[i]), addr, 1);
// 		__m256 Yimaginary = _mm256_i32gather_ps(&((const float *)&(Y_cast[i]))[1], addr, 1);

// 		__m256 res_real_a = _mm256_dp_ps(Xreal, Yreal, 0xFF);
// 		__m256 res_real_b = _mm256_dp_ps(Ximaginary, Yimaginary, 0xFF);

// 		__m256 res_imaginary_a = _mm256_dp_ps(Xreal, Yimaginary, 0xFF);
// 		__m256 res_imaginary_b = _mm256_dp_ps(Ximaginary, Yreal, 0xFF);

// 		_mm256_store_ps(dot_real_a, res_real_a);
// 		_mm256_store_ps(dot_real_b, res_real_b);
// 		_mm256_store_ps(dot_imaginary_a, res_imaginary_a);
// 		_mm256_store_ps(dot_imaginary_b, res_imaginary_b);

// 		dot_real_total += dot_real_a[0] - dot_real_b[0];
// 		dot_imaginary_total += dot_imaginary_a[0] + dot_imaginary_b[0];
// 	}

// 	complexe_float_t *dot = ((complexe_float_t *)dotu);
// 	dot->imaginary = dot_imaginary_total;
// 	dot->real = dot_real_total;
// }

void mncblas_cdotu_V(const int N, const void *X, const int incX, const void *Y, const int incY,
					 void *dotu) {
	register unsigned int i = 0;
	register unsigned int j = 0;
	const complexe_float_t *X_cast = (const complexe_float_t *)X;
	const complexe_float_t *Y_cast = (const complexe_float_t *)Y;

	float dot_real_total = 0.0;
	float dot_imaginary_total = 0.0;

	register __m256i addr = _mm256_set_epi32(8 * 7, 8 * 6, 8 * 5, 8 * 4, 8 * 3, 8 * 2, 8 * 1, 0);

	for (i = 0; i < N; i += (256 / (sizeof(float) * 8))) {
		float dot_real[8];
		float dot_imaginary[8];

		__m256 Xreal = _mm256_i32gather_ps((const float *)&(X_cast[i]), addr, 1);
		__m256 Ximaginary = _mm256_i32gather_ps(&((const float *)&(X_cast[i]))[1], addr, 1);


		__m256 Yreal = _mm256_i32gather_ps((const float *)&(Y_cast[i]), addr, 1);
		__m256 Yimaginary = _mm256_i32gather_ps(&((const float *)&(Y_cast[i]))[1], addr, 1);

		__m256 res_real =
			_mm256_sub_ps(_mm256_mul_ps(Xreal, Yreal), _mm256_mul_ps(Ximaginary, Yimaginary));
		__m256 res_imaginary =
			_mm256_add_ps(_mm256_mul_ps(Xreal, Yimaginary), _mm256_mul_ps(Ximaginary, Yreal));

		_mm256_store_ps(dot_real, res_real);
		_mm256_store_ps(dot_imaginary, res_imaginary);

		for (j = 0; j < 8; j++) {
			dot_real_total += dot_real[j];
			dot_imaginary_total += dot_imaginary[j];
		}
	}

	complexe_float_t *dot = ((complexe_float_t *)dotu);
	dot->imaginary = dot_imaginary_total;
	dot->real = dot_real_total;
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
