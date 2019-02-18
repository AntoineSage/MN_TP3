#include <stdio.h>
#include <x86intrin.h>

#include "mnblas.h"
#include "complexe.h"

#include "flop.h"

#define VECSIZE    1024

#define NB_FOIS    5

typedef float vfloat [VECSIZE] ;

vfloat vec1, vec2 ;

void vector_init (vfloat V, float x)
{
  register unsigned int i ;

  for (i = 0; i < VECSIZE; i++)
    V [i] = x ;

  return ;
}

void vector_print (vfloat V)
{
  register unsigned int i ;

  for (i = 0; i < VECSIZE; i++)
    printf ("%f ", V[i]) ;
  printf ("\n") ;
  
  return ;
}

int main (int argc, char **argv)
{
 unsigned long long start, end ;
 float res ;
 int i ;

 for (i = 0 ; i < NB_FOIS; i++)
   {
     vector_init (vec1, 1.0) ;
     vector_init (vec2, 2.0) ;

     start = _rdtsc () ;
        res = mncblas_sdot (VECSIZE, vec1, 1, vec2, 1) ;
     end = _rdtsc () ;
     
     printf ("mncblas_sdot %d : res = %3.2f nombre de cycles: %Ld \n", i, res, end-start) ;
     calcul_flop ("sdot ", 2 * VECSIZE, end-start) ;
   }
}
