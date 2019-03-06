#include "mnblas.h"
#include "complexe.h"
#include "math.h"


float mncblas_sasum (const int n, const float *X, const int incx){

  register unsigned int i = 0 ;
	register float sum=0;

  for (;(i<n); i += incX)
    {
      sum=sum+abs(X[i]);
    }

  return sum;

}

float mncblas_scasum (const int n, const void *X, const int incx){

  register unsigned int i = 0 ;
	register float sum=0;

  for (;(i<n); i += incX)
    {
      sum=sum+abs(((complexe_float_t)X)[i].real)+abs(((complexe_float_t)X)[i].imaginary);
    }

  return sum;

}

}

double mncblas_dasum (const int n, const double *X, const int incx){

  register unsigned int i = 0 ;
	register double sum=0;

  for (;(i<n); i += incX)
    {
      sum=sum+abs(X[i]);
    }

  return sum;

}

double mncblas_dzasum (const int n, const void *X, const int incx){

  register unsigned int i = 0 ;
	register double sum=0;

  for (;(i<n); i += incX)
    {
      sum=sum+abs(((complexe_double_t)X)[i].real)+abs(((complexe_double_t)X)[i].imaginary);
    }

  return sum;

}

