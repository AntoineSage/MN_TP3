#include <stdio.h>
#include <x86intrin.h>

#include <complexe.h>
#include <mnblas.h>

#include "flop.h"
#include "perf_utils.h"

void perf_float() {
	vfloat vec1, vec2;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		vector_init(vec1, 1.0);
		vector_init(vec2, 2.0);

		start = _rdtsc();
		mncblas_saxpy(VECSIZE, 3, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("sdot : ", 2 * VECSIZE, mean);
}

void perf_double() {
	vdouble vec1, vec2;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		vector_init_d(vec1, 1.0);
		vector_init_d(vec2, 2.0);

		start = _rdtsc();
		mncblas_daxpy(VECSIZE, 3, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("ddot : ", 2 * VECSIZE, mean);
}

void perf_complex() {
	vcomplex vec1, vec2;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		complexe_float_t c1;
		c1.imaginary = 1.0;
		c1.real = 2.0;

		complexe_float_t c2;
		c1.imaginary = 3.0;
		c1.real = 3.0;

		complexe_float_t c3[1];
		c3[0].imaginary = 2.0;
		c3[0].real = 2.0;

		vector_init_c(vec1, c1);
		vector_init_c(vec2, c2);

		start = _rdtsc();
		mncblas_caxpy(VECSIZE, c3, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("cdotu : ", 8 * VECSIZE, mean);
}

void perf_complex_double() {
	vcomplexd vec1, vec2;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		complexe_double_t c1;
		c1.imaginary = 1.0;
		c1.real = 2.0;

		complexe_double_t c2;
		c1.imaginary = 3.0;
		c1.real = 3.0;

		complexe_double_t c3[1];
		c3[0].imaginary = 2.0;
		c3[0].real = 2.0;

		vector_init_z(vec1, c1);
		vector_init_z(vec2, c2);

		start = _rdtsc();
		mncblas_caxpy(VECSIZE, c3, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("cdotu : ", 8 * VECSIZE, mean);
}

int main(int argc, char **argv) {
	perf_float();
	perf_double();
	perf_complex();
	perf_complex_double();
}