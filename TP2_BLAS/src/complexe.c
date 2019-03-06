#include <complexe.h>
#include <math.h>

complexe_float_t add_complexe_float(const complexe_float_t c1, const complexe_float_t c2) {
	complexe_float_t r;

	r.real = c1.real + c2.real;
	r.imaginary = c1.imaginary + c2.imaginary;

	return r;
}

complexe_double_t add_complexe_double(const complexe_double_t c1, const complexe_double_t c2) {
	complexe_double_t r;

	r.real = c1.real + c2.real;
	r.imaginary = c1.imaginary + c2.imaginary;

	return r;
}

complexe_float_t mult_complexe_float(const complexe_float_t c1, const complexe_float_t c2) {
	complexe_float_t r;

	r.real = (c1.real * c2.real) - (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) + (c1.imaginary * c2.real);

	return r;
}

complexe_double_t mult_complexe_double(const complexe_double_t c1, const complexe_double_t c2) {
	complexe_double_t r;

	r.real = (c1.real * c2.real) - (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) + (c1.imaginary * c2.real);

	return r;
}

complexe_float_t mult_complexe_conjug_float(const complexe_float_t c1, const complexe_float_t c2) {
	complexe_float_t r;

	r.real = (c1.real * c2.real) + (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) - (c1.imaginary * c2.real);

	return r;
}

complexe_double_t mult_complexe_conjug_double(const complexe_double_t c1,
											  const complexe_double_t c2) {
	complexe_double_t r;

	r.real = (c1.real * c2.real) + (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) - (c1.imaginary * c2.real);

	return r;
}

int complexe_equal_float(const complexe_float_t a, const complexe_float_t b) {
	return (a.real == b.real) && (a.imaginary == b.imaginary);
}

int complexe_equal_double(const complexe_double_t a, const complexe_double_t b) {
	return (a.real == b.real) && (a.imaginary == b.imaginary);
}

float module_complexe_float(const complexe_float_t a) {
	return sqrt(a.real * a.real + a.imaginary * a.imaginary);
}

double module_complexe_double(const complexe_double_t a) {
	return sqrt(a.real * a.real + a.imaginary * a.imaginary);
}

float module_complexe_squared_float(const complexe_float_t a) {
	return a.real * a.real + a.imaginary * a.imaginary;
}

double module_complexe_squared_double(const complexe_double_t a) {
	return a.real * a.real + a.imaginary * a.imaginary;
}