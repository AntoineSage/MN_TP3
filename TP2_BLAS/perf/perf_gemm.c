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

	int size = (int)sqrt(VECSIZE);
	for (int i = 0; i < NB_FOIS; i++) {
		vector_init(vec1, 1.0);
		vector_init(vec2, 2.0);
		vector_init(vec3, 3.0);

		start = _rdtsc();
		mncblas_sgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, size, size, size, -1.0, vec1,
					  0, vec2, 0, 2.0, vec3, 0);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("sdot : ", VECSIZE * (3 + size * 2), mean);
}

void perf_double() {
	vdouble vec1, vec2, vec3;
	unsigned long long start, end;
	float mean = 0.0;

	int size = (int)sqrt(VECSIZE);
	for (int i = 0; i < NB_FOIS; i++) {
		vector_init_d(vec1, 1.0);
		vector_init_d(vec2, 2.0);
		vector_init_d(vec3, 3.0);

		start = _rdtsc();
		mncblas_dgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, size, size, size, -1.0, vec1,
					  0, vec2, 0, 2.0, vec3, 0);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("ddot : ", VECSIZE * (3 + size * 2), mean);
}

void perf_complex() {
	vcomplex vec1, vec2, vec3;
	unsigned long long start, end;
	float mean = 0.0;

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

	int size = (int)sqrt(VECSIZE);

	for (int i = 0; i < NB_FOIS; i++) {
		vector_init_c(vec1, c1);
		vector_init_c(vec2, c2);
		vector_init_c(vec3, c3);

		start = _rdtsc();
		mncblas_cgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, size, size, size, &alpha,
					  vec1, 0, vec2, 0, &beta, vec3, 0);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("cdotu : ", VECSIZE * (14 + size * 8), mean);
}

void perf_complex_double() {
	vcomplexd vec1, vec2, vec3;
	unsigned long long start, end;
	float mean = 0.0;

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

	int size = (int)sqrt(VECSIZE);

	for (int i = 0; i < NB_FOIS; i++) {
		vector_init_z(vec1, c1);
		vector_init_z(vec2, c2);
		vector_init_z(vec3, c3);

		start = _rdtsc();
		mncblas_zgemm(MNCblasRowMajor, MNCblasNoTrans, MNCblasNoTrans, size, size, size, &alpha,
					  vec1, 0, vec2, 0, &beta, vec3, 0);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("cdotu : ", VECSIZE * (14 + size * 8), mean);
}

int main(int argc, char **argv) {
	perf_float();
	perf_double();
	perf_complex();
	perf_complex_double();
}
