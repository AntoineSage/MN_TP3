#include <complexe.h>

void init_complexe_double(const int N, const double *a, const double *b, const void *res) {
	register unsigned int i = 0;

	for (; (i < N); i++) {
		(((complexe_double_t *)res)[i]).real = a[i];
		(((complexe_double_t *)res)[i]).imaginary = b[i];
	}

	return;
}

int complexe_equal_float(const complexe_float_t a, const complexe_float_t b) {
	return (a.real == b.real) && (a.imaginary == b.imaginary);
}

int complexe_equal_double(const complexe_double_t a, const complexe_double_t b) {
	return (a.real == b.real) && (a.imaginary == b.imaginary);
}
