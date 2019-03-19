#include "perf_utils.h"
#include <stdio.h>

void vector_init(vfloat V, float x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE; i++)
		V[i] = x;

	return;
}

void vector_print(vfloat V) {
	register unsigned int i;

	for (i = 0; i < VECSIZE; i++)
		printf("%f ", V[i]);
	printf("\n");

	return;
}
