#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "poly_creux.h"

/*void test_egalite_polynome()
{
  p_polyf_t p1, p2;
  p1 = lire_polynome_float("p1");
  p2 = lire_polynome_float("p2");

  assert(egalite_polynome(p1, p1));
  assert(egalite_polynome(p2, p2));
  assert(!egalite_polynome(p1, p2));
}
*/

int main(int argc, char **argv)
{
  p_polycreux_t p1, p2,p3;

  if (argc != 3)
  {
    fprintf(stderr, "deux paramètres (polynomes,fichiers) sont à passer \n");
    exit(-1);
  }
  p1 = lire_polynome_float(argv[1]);
  p2 = lire_polynome_float(argv[2]);

  ecrire_polynome_float(p1);
  ecrire_polynome_float(p2);

/*	p3=addition_polynome(p1,p2);
	printf("Addition de p1 et p2:\n");  
	ecrire_polynome_float (p3) ;
	p3=multiplication_polynome_scalaire(p1,3);
	printf("Multiplication de p1 par 3:\n"); 
	ecrire_polynome_float (p3) ;
	p3=puissance_polynome(p1,2);
	printf("p1 puissance 2:\n"); 
	ecrire_polynome_float (p3) ;
	p3=composition_polynome(p1,p2); 
	printf("Composée de p1 et p2:\n"); 
	ecrire_polynome_float (p3) ; */

}
