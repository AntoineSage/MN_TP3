#include <complexe.h>

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

complexe_float_t mult_scalaire_float(const complexe_float_t c, const float a){
	complexe_float_t r;
	r.real = a*c.real;
	r.imaginary = a*c.imaginary;
	return r;
}

complexe_double_t mult_scalaire_float(const complexe_double_t c, const float a){
	complexe_double_t r;
	r.real = a*c.real;
	r.imaginary = a*c.imaginary;
	return r;
}

complexe_float_t mult_complexe_float (const complexe_float_t c1, const complexe_float_t c2)
{
  complexe_float_t r ;

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

void init_complexe_double(const int N, const double *a, const double *b, const void *res){
	
	register unsigned int i = 0 ;

	for (; (i < N); i++)
    {
    	((complexe_double_t*)res[i]).real = a[i];
		((complexe_double_t*)res[i]).imaginary = b[i];
    }

	return ;

 }