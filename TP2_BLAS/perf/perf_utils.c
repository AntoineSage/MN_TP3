#include "perf_utils.h"
#include <stdio.h>

void vector_init(vfloat V, float x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE; i++)
		V[i] = x;
}

void vector_init_d(vdouble V, double x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE; i++)
		V[i] = x;
}

void vector_init_c(vcomplex V, complexe_float_t x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE; i++)
		V[i] = x;
}

void vector_init_z(vcomplexd V, complexe_double_t x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE; i++)
		V[i] = x;
}

void mat_init(vfloat V, float x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE*VECSIZE; i++)
		V[i] = x;
}

void mat_init_d(vdouble V, double x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE*VECSIZE; i++)
		V[i] = x;
}

void mat_init_c(vcomplex V, complexe_float_t x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE*VECSIZE; i++)
		V[i] = x;
}

void mat_init_z(vcomplexd V, complexe_double_t x) {
	register unsigned int i;

	for (i = 0; i < VECSIZE*VECSIZE; i++)
		V[i] = x;
}


void vector_print(vfloat V) {
	register unsigned int i;

	for (i = 0; i < VECSIZE; i++)
		printf("%f ", V[i]);
	printf("\n");
}
