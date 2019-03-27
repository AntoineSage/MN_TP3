#include "mnblas.h"
#include "complexe.h"

void mncblas_sswap(const int N, float *X, const int incX, 
                 float *Y, const int incY)
{
  register unsigned int i = 0 ;
  register unsigned int j = 0 ;
  register float save ;
  
  for (; ((i < N) && (j < N)) ; i += incX, j+=incY)
    {
      save = Y [j] ;
      Y [j] = X [i] ;
      X [i] = save ;
    }

  return ;
}

void mncblas_dswap(const int N, double *X, const int incX, 
                 double *Y, const int incY)
{
  register unsigned int i = 0 ;
  register unsigned int j = 0 ;
  register float save ;
  
  for (; ((i < N) && (j < N)) ; i += incX, j+=incY)
    {
      save = Y [j] ;
      Y [j] = X [i] ;
      X [i] = save ;
    }

	return;
}

void mncblas_cswap(const int N, void *X, const int incX, void *Y, const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;
	register complexe_float_t save;

	register complexe_float_t *X_c = (complexe_float_t *)X;
	register complexe_float_t *Y_c = (complexe_float_t *)Y;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		save = Y_c[i];
		Y_c[j] = X_c[i];
		X_c[i] = save;
	}

	return;
}

void mncblas_zswap(const int N, void *X, const int incX, void *Y, const int incY) {
	register unsigned int i = 0;
	register unsigned int j = 0;
	register complexe_double_t save;

	register complexe_double_t *X_c = (complexe_double_t *)X;
	register complexe_double_t *Y_c = (complexe_double_t *)Y;

	for (; ((i < N) && (j < N)); i += incX, j += incY) {
		save = Y_c[i];
		Y_c[j] = X_c[i];
		X_c[i] = save;
	}

	return;
}
