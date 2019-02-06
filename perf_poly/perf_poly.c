#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "poly.h"

#include <x86intrin.h>

static const float duree_cycle = (float) 1 / (float) 2.6 ; // duree du cycle en nano seconde 10^-9

void calcul_flop (char *message, int nb_operations_flottantes, unsigned long long int cycles)
{
  printf ("%s %d operations %f GFLOP/s\n", message, nb_operations_flottantes, ((float) nb_operations_flottantes) / (((float) cycles) * duree_cycle)) ;
  return ;
}

int main (int argc, char **argv)
{
  p_polyf_t p1, p2, p3, p4, p5, p6 ;
  unsigned long long start, end ;
  
  if (argc != 3)
    {
      fprintf (stderr, "deux paramètres (polynomes,fichiers) sont à passer \n") ;
      exit (-1) ;
    }
      
  p1 = lire_polynome_float (argv [1]) ;
  p2 = lire_polynome_float (argv [2]) ;

  printf ("p1 = ") ;
  ecrire_polynome_float (p1) ;

  printf ("p2 = ") ;
  ecrire_polynome_float (p2) ;

  /*
    ajouter du code pour tester les fonctions
    sur les polynomes
  */

  start = _rdtsc () ;
  
        p3 = addition_polynome (p1, p2) ;

  end = _rdtsc () ;

  printf ("p3 = ") ;
  ecrire_polynome_float (p3) ;
  
  printf ("addition %Ld\n", end-start) ;
  calcul_flop ("p1+p2", min(p1->degre, p2->degre)+1, end-start) ;
  detruire_polynome (p3) ;

  p4 = creer_polynome (1024) ;
  p5 = creer_polynome (1024) ;

  init_polynome (p4, 1.0) ;
  init_polynome (p5, 2.0) ;

    start = _rdtsc () ;
  
        p6 = addition_polynome (p4, p5) ;

  end = _rdtsc () ;

  printf ("addition %Ld\n", end-start) ;
  calcul_flop ("p4+p5", min(p4->degre, p5->degre)+1, end-start) ;
  detruire_polynome (p6);

	void perf_addition_polynome(int taille){

		p_polyf_t p1 = creer_polynome (taille-1);
		p_polyf_t pvide = creer_polynome (taille-1);
		init_polynome(p1, 2);
		init_polynome(pvide, 0);

		p_polyf_t p2 = creer_polynome (taille-1);
		p_polyf_t p3 = creer_polynome (taille-1);
		p_polyf_t p5 = creer_polynome (taille-1);
		init_polynome_half_zero(p2, 2);
		init_polynome_half_zero(p3, 3);
		init_polynome_half_zero(p5, 5);

		p_polycreux_t p1c = creer_polynome_creux (taille);			
		p_polycreux_t pvidec = creer_polynome_creux (taille);
		init_polynome_creux(p1c, 2);
		init_polynome_creux(pvidec, 2);

		p_polycreux_t p2c = creer_polynome_creux (taille);			
		p_polycreux_t p3c = creer_polynome_creux (taille);
		p_polycreux_t p5c = creer_polynome_creux (taille);
		init_polynome_creux_half_zero(p2c, 2);
		init_polynome_creux_half_zero(p3c, 3);
		init_polynome_creux_half_zero(p5c, 5);
		
		unsigned long long start, end ;
		
		printf("Addition\n");
		start = _rdtsc () ;
		p_polyf_t p4 = addition_polynome(p1,pvide);
		end = _rdtsc () ;
		calcul_flop("\t P",taille,end-start);
		assert(egalite_polynome(p1, p4));

		printf("Addition avec 0\n");
		start = _rdtsc () ;
		p_polyf_t p6 = addition_polynome(p2,p3);
		end = _rdtsc () ;
		calcul_flop("\t P",taille/2,end-start);
		assert(egalite_polynome(p5, p6));
		
		printf("Addition creux\n");
		start = _rdtsc () ;
		p_polycreux_t p4c = addition_polynome_creux(p1c,pvidec);
		end = _rdtsc () ;
		calcul_flop("\t C",taille,end-start);
		assert(egalite_polynome_creux(p1c, p4c));

		printf("Addition creux avec 0\n");
		start = _rdtsc () ;
		p_polycreux_t p6c = addition_polynome_creux(p2c,p3c);
		end = _rdtsc () ;
		calcul_flop("\t C",taille/2,end-start);
		assert(egalite_polynome_creux(p5c, p6c));

	}


  
  
}
