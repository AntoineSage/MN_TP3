#include "mnblas.h"
#include "complexe.h"


void mncblas_saxpy (const int N, const float a, const float *X, const int incX, float *Y, const int incY){

  register unsigned int i = 0 ;
	register unsigned int j = 0 ;

  for (; ((i < N) && (j < N)) ; i += incX, j+=incY)
    {
      Y[j] = a*X[i] + Y[j];
    }

  return ;
}

void mncblas_daxpy (const int N, const double a, const double *X, const int incX, double *Y, const int incY){

  register unsigned int i = 0 ;
	register unsigned int j = 0 ;

  for (; ((i < N) && (j < N)) ; i += incX, j+=incY)
    {
      Y[j] = a*X[i] + Y[j];
    }

  return ;
}

void mncblas_caxpy (const int N, const void *a, const void *X, const int incX, void *Y, const int incY){

  register unsigned int i = 0 ;
	register unsigned int j = 0 ;

  register complexe_float_t *X_c = (complexe_float_t *)X;
	register complexe_float_t *Y_c = (complexe_float_t *)Y;
  register complexe_float_t *a_c = (complexe_float_t *)a;

  for (; ((i < N) && (j < N)) ; i += incX, j+=incY)
    {
      Y_c[j] = add_complexe_float(mult_complexe_float (X_c[i], a_c[0]),Y_c[j]);
    }

  return ;
}

void mncblas_zaxpy (const int N, const void *a, const void *X, const int incX, void *Y, const int incY){

  register unsigned int i = 0 ;
	register unsigned int j = 0 ;

  register complexe_double_t *X_c = (complexe_double_t *)X;
	register complexe_double_t *Y_c = (complexe_double_t *)Y;
  register complexe_double_t *a_c = (complexe_double_t *)a;

  for (; ((i < N) && (j < N)) ; i += incX, j+=incY)
    {
      Y_c[j] = add_complexe_double(mult_complexe_double (X_c[i], a_c[0]),Y_c[j]);
    }

  return ;
}


