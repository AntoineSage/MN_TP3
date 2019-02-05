#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "poly_creux.h"

void test_addition_polynome() {
	p_polycreux_t p1 = lire_polynome_float("p1c");
	p_polycreux_t p2 = lire_polynome_float("pvidec");
	assert(egalite_polynome(p1, addition_polynome(p1, p2)));

	p_polycreux_t p3 = multiplication_polynome_scalaire(p1, 2);
	p_polycreux_t p4 = addition_polynome(p1, p1);
	assert(egalite_polynome(p3, p4));

	p1 = lire_polynome_float("p1c");
	p2 = lire_polynome_float("p2c");
	p3 = lire_polynome_float("p3c");
	assert(egalite_polynome(p3, addition_polynome(p1, p2)));
}

void test_egalite_polynome() {
	p_polycreux_t p1 = lire_polynome_float("p1c");
	p_polycreux_t p2 = lire_polynome_float("p2c");

	assert(egalite_polynome(p1, p1));
	assert(!egalite_polynome(p1, p2));
}

void test_multiplication_polynome_scalaire() {
	p_polycreux_t p1 = lire_polynome_float("p1c");
	p_polycreux_t p2 = multiplication_polynome_scalaire(p1, -1.0);
	
	p_polycreux_t p3 = lire_polynome_float("pvidec");

	assert(egalite_polynome(p3, addition_polynome(p1, p2)));
}

void test_eval_polynome() {
	p_polycreux_t p1 = lire_polynome_float("pvidec");
	assert(eval_polynome(p1, 10) == 0.0);

	p1 = lire_polynome_float("p1c");
	assert(eval_polynome(p1, 0) == 2.0);
	assert(eval_polynome(p1, 1) == 9.0);
	assert(eval_polynome(p1, 2) == 46.0);
}

void assert_no_deg_0(p_polycreux_t p) {
	register unsigned int i;
	for (i = 0; i < p->nelem; i++) {
		assert(p->tab_paires[i].coeff != 0.0);
	}
}

	
	/*p3=addition_polynome(p1,p2);
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

void assert_croissant(p_polycreux_t p) {
	register unsigned int i;
	for (i = 0; i < p->nelem - 1; i++) {
		assert(p->tab_paires[i].degre < p->tab_paires[i + 1].degre);
	}
}

int main(int argc, char **argv) {
	p_polycreux_t p1, p2;

	if (argc != 3) {
		fprintf(stderr, "deux paramètres (polynomes,fichiers) sont à passer \n");
		exit(-1);
	}
	p1 = lire_polynome_float(argv[1]);
	p2 = lire_polynome_float(argv[2]);

	ecrire_polynome_float(p1);
	ecrire_polynome_float(p2);

	test_egalite_polynome();
	printf("egalite OK\n");
	test_addition_polynome();
	printf("addition OK\n");
	test_multiplication_polynome_scalaire();
	printf("multiplication OK\n");
	test_eval_polynome();
	printf("eval OK\n");
}

