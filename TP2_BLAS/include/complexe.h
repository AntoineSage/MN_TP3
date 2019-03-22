#ifndef _COMPLEXE_H_
#define _COMPLEXE_H_

#include <math.h>

typedef struct {
	float real;
	float imaginary;
} complexe_float_t;

typedef struct {
	double real;
	double imaginary;
} complexe_double_t;

static inline complexe_float_t add_complexe_float(const complexe_float_t c1,
												  const complexe_float_t c2) {
	complexe_float_t r;

	r.real = c1.real + c2.real;
	r.imaginary = c1.imaginary + c2.imaginary;

	return r;
}

static inline complexe_double_t add_complexe_double(const complexe_double_t c1,
													const complexe_double_t c2) {
	complexe_double_t r;

	r.real = c1.real + c2.real;
	r.imaginary = c1.imaginary + c2.imaginary;

	return r;
}

static inline complexe_float_t mult_scalaire_float(const complexe_float_t c, const float a) {
	complexe_float_t r;
	r.real = a * c.real;
	r.imaginary = a * c.imaginary;
	return r;
}

static inline complexe_double_t mult_scalaire_double(const complexe_double_t c, const double a) {
	complexe_double_t r;
	r.real = a * c.real;
	r.imaginary = a * c.imaginary;
	return r;
}

static inline complexe_float_t mult_complexe_float(const complexe_float_t c1,
												   const complexe_float_t c2) {
	complexe_float_t r;

	r.real = (c1.real * c2.real) - (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) + (c1.imaginary * c2.real);

	return r;
}

static inline complexe_double_t mult_complexe_double(const complexe_double_t c1,
													 const complexe_double_t c2) {
	complexe_double_t r;

	r.real = (c1.real * c2.real) - (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) + (c1.imaginary * c2.real);

	return r;
}

static inline complexe_float_t mult_complexe_conjug_float(const complexe_float_t c1,
														  const complexe_float_t c2) {
	complexe_float_t r;

	r.real = (c1.real * c2.real) + (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) - (c1.imaginary * c2.real);

	return r;
}

static inline complexe_double_t mult_complexe_conjug_double(const complexe_double_t c1,
															const complexe_double_t c2) {
	complexe_double_t r;

	r.real = (c1.real * c2.real) + (c1.imaginary * c2.imaginary);
	r.imaginary = (c1.real * c2.imaginary) - (c1.imaginary * c2.real);

	return r;
}

int complexe_equal_float(const complexe_float_t a, const complexe_float_t b);
int complexe_equal_double(const complexe_double_t a, const complexe_double_t b);

static inline float module_complexe_float(const complexe_float_t a) {
	return sqrt(a.real * a.real + a.imaginary * a.imaginary);
}

static inline double module_complexe_double(const complexe_double_t a) {
	return sqrt(a.real * a.real + a.imaginary * a.imaginary);
}

static inline float module_complexe_squared_float(const complexe_float_t a) {
	return a.real * a.real + a.imaginary * a.imaginary;
}

static inline double module_complexe_squared_double(const complexe_double_t a) {
	return a.real * a.real + a.imaginary * a.imaginary;
}

static inline int iszero_float(const complexe_float_t a) {
	return a.real == 0 && a.imaginary == 0;
}

static inline int iszero_double(const complexe_double_t a) {
	return a.real == 0 && a.imaginary == 0;
}

static inline int isone_float(const complexe_float_t a) {
	return a.real == 1 && a.imaginary == 0;
}

static inline int isone_double(const complexe_double_t a) {
	return a.real == 1 && a.imaginary == 0;
}
#endif
