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
		mncblas_sswap(VECSIZE, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;

	printf("Moyenne sur %d répétitions : ", NB_FOIS);
	calcul_flop("sswap : ", 2 * VECSIZE, mean);
}

int main(int argc, char **argv) {
	perf_float();
	return;
}
