#include <stdio.h>
#include <x86intrin.h>

#include <complexe.h>
#include <math.h>
#include <mnblas.h>

#include "flop.h"
#include "perf_utils.h"

void perf_float() {
	vfloat vec1, vec2, vec3;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec1[j] = 1.0;
		}

		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec2[j] = 2.0;
		}

		vector_init(vec3, 3.0);
		vector_init(vec1, 1.0);
		vector_init(vec2, 2.0);

		start = _rdtsc();
		mncblas_sgemv(MNCblasRowMajor, MNCblasNoTrans, floor(sqrt(VECSIZE)), floor(sqrt(VECSIZE)),
					  5, vec3, 0, vec1, 1, 3, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("sgemv : ", floor(sqrt(VECSIZE)) + 1 + VECSIZE * 3, mean);
}

void perf_double() {
	vdouble vec1, vec2, vec3;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec1[j] = 1.0;
		}

		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec2[j] = 2.0;
		}

		vector_init_d(vec3, 3.0);

		start = _rdtsc();
		mncblas_dgemv(MNCblasRowMajor, MNCblasNoTrans, floor(sqrt(VECSIZE)), floor(sqrt(VECSIZE)),
					  5, vec3, 0, vec1, 1, 3, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("dgemv : ", floor(sqrt(VECSIZE)) + 1 + VECSIZE * 3, mean);
}

void perf_complexe_float() {
	vcomplex vec1, vec2, vec3;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		complexe_float_t c1;
		c1.imaginary = 1.0;
		c1.real = 1.0;

		complexe_float_t c2;
		c2.imaginary = 2.0;
		c2.real = 2.0;

		complexe_float_t c3;
		c2.imaginary = 3.0;
		c2.real = 3.0;

		complexe_float_t alpha;
		alpha.imaginary = -1.0;
		alpha.real = -1.0;

		complexe_float_t beta;
		beta.imaginary = 2.0;
		beta.real = 2.0;

		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec1[j] = c1;
		}

		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec2[j] = c2;
		}

		vector_init_c(vec3, c3);

		start = _rdtsc();
		mncblas_cgemv(MNCblasRowMajor, MNCblasNoTrans, floor(sqrt(VECSIZE)), floor(sqrt(VECSIZE)),
					  &alpha, vec3, 0, vec1, 1, &beta, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("cgemv : ", (floor(sqrt(VECSIZE)) + 1) * 6 + VECSIZE * 14, mean);
}

void perf_complexe_double() {
	vcomplexd vec1, vec2, vec3;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		complexe_double_t c1;
		c1.imaginary = 1.0;
		c1.real = 1.0;

		complexe_double_t c2;
		c2.imaginary = 2.0;
		c2.real = 2.0;

		complexe_double_t c3;
		c2.imaginary = 3.0;
		c2.real = 3.0;

		complexe_double_t alpha;
		alpha.imaginary = -1.0;
		alpha.real = -1.0;

		complexe_double_t beta;
		beta.imaginary = 2.0;
		beta.real = 2.0;

		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec1[j] = c1;
		}

		for (int j = 0; j < sqrt(VECSIZE); j++) {
			vec2[j] = c2;
		}

		vector_init_z(vec3, c3);

		start = _rdtsc();
		mncblas_zgemv(MNCblasRowMajor, MNCblasNoTrans, floor(sqrt(VECSIZE)), floor(sqrt(VECSIZE)),
					  &alpha, vec3, 0, vec1, 1, &beta, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("cgemv : ", (floor(sqrt(VECSIZE)) + 1) * 6 + VECSIZE * 14, mean);
}

int main(int argc, char const* argv[]) {
	perf_float();
	perf_double();
	perf_complexe_float();
	perf_complexe_double();
}