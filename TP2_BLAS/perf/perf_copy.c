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

		start = _rdtsc();
		mncblas_scopy(VECSIZE, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_mo("scopy : ", VECSIZE, sizeof(float), mean);
}

void perf_double() {
	vdouble vec1, vec2;
	unsigned long long start, end;
	float mean = 0.0;

	for (int i = 0; i < NB_FOIS; i++) {
		vector_init_d(vec1, 1.0);

		start = _rdtsc();
		mncblas_dcopy(VECSIZE, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_mo("scopy : ", VECSIZE, sizeof(double), mean);
}

void perf_complex() {
	vcomplex vec1, vec2;
	unsigned long long start, end;
	float mean = 0.0;

	complexe_float_t c;
	c.imaginary = 1.0;
	c.real = 1.0;
	for (int i = 0; i < NB_FOIS; i++) {
		vector_init_c(vec1, c);

		start = _rdtsc();
		mncblas_ccopy(VECSIZE, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_mo("scopy : ", VECSIZE, sizeof(complexe_float_t), mean);
}

void perf_complex_double() {
	vcomplexd vec1, vec2;
	unsigned long long start, end;
	float mean = 0.0;

	complexe_double_t c;
	c.imaginary = 1.0;
	c.real = 1.0;
	for (int i = 0; i < NB_FOIS; i++) {
		vector_init_z(vec1, c);

		start = _rdtsc();
		mncblas_zcopy(VECSIZE, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_mo("scopy : ", VECSIZE, sizeof(complexe_double_t), mean);
}

int main(int argc, char **argv) {
	perf_float();
	perf_double();
	perf_complex();
	perf_complex_double();
}
