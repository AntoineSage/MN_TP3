#include <stdio.h>
#include <x86intrin.h>

#include <complexe.h>
#include <mnblas.h>

#include "flop.h"
#include "perf_utils.h"

vfloat vec1, vec2;

int main(int argc, char **argv) {
	unsigned long long start, end;
	float mean = 0.0;

	int i;
	for (i = 0; i < NB_FOIS; i++) {
		vector_init(vec1, 1.0);
		vector_init(vec2, 2.0);

		start = _rdtsc();
		mncblas_sdot(VECSIZE, vec1, 1, vec2, 1);
		end = _rdtsc();
		mean += end - start;
	}
	mean /= NB_FOIS;
	calcul_flop("sdot, en moyenne : ", 2 * VECSIZE, mean);
}
