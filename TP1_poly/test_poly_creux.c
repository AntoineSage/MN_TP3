#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "poly_creux.h"

void test_addition_polynome_creux() {
	p_polycreux_t p1 = lire_polynome_float_creux("p1c");
	p_polycreux_t p2 = lire_polynome_float_creux("pvidec");
	assert(egalite_polynome_creux(p1, addition_polynome_creux(p1, p2)));

	p_polycreux_t p3 = multiplication_polynome_scalaire_creux(p1, 2);
	p_polycreux_t p4 = addition_polynome_creux(p1, p1);
	assert(egalite_polynome_creux(p3, p4));

	p1 = lire_polynome_float_creux("p1c");
	p2 = lire_polynome_float_creux("p2c");
	p3 = lire_polynome_float_creux("p3c");
	assert(egalite_polynome_creux(p3, addition_polynome_creux(p1, p2)));
}

void test_egalite_polynome_creux() {
	p_polycreux_t p1 = lire_polynome_float_creux("p1c");
	p_polycreux_t p2 = lire_polynome_float_creux("p2c");

	assert(egalite_polynome_creux(p1, p1));
	assert(!egalite_polynome_creux(p1, p2));
}

void test_multiplication_polynome_scalaire_creux() {
	p_polycreux_t p1 = lire_polynome_float_creux("p1c");
	p_polycreux_t p2 = multiplication_polynome_scalaire_creux(p1, -1.0);
}

void test_multiplication_polynomes_creux() {
	p_polycreux_t p1 = lire_polynome_float_creux("p1c");
	p_polycreux_t p2 = lire_polynome_float_creux("pvidec");
	p_polycreux_t p3 = multiplication_polynomes_creux(p1, p2);

	assert(egalite_polynome_creux(p3, p2));
}

void test_eval_polynome_creux() {
	p_polycreux_t p1 = lire_polynome_float_creux("pvidec");
	assert(eval_polynome_creux(p1, 10) == 0.0);

	p1 = lire_polynome_float_creux("p1c");
	assert(eval_polynome_creux(p1, 0) == 2.0);
	assert(eval_polynome_creux(p1, 1) == 9.0);
	assert(eval_polynome_creux(p1, 2) == 46.0);
}

void assert_no_deg_0(p_polycreux_t p) {
	register unsigned int i;
	for (i = 0; i < p->nelem; i++) {
		assert(p->tab_paires[i].coeff != 0.0);
	}
}

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
	p1 = lire_polynome_float_creux(argv[1]);
	p2 = lire_polynome_float_creux(argv[2]);

	ecrire_polynome_float_creux(p1);
	ecrire_polynome_float_creux(p2);

	test_egalite_polynome_creux();
	printf("egalite OK\n");
	test_addition_polynome_creux();
	printf("addition OK\n");
	test_multiplication_polynome_scalaire_creux();
	printf("multiplication scalaire OK\n");
	test_multiplication_polynomes_creux();
	printf("multiplication polynomes OK\n");
	test_eval_polynome_creux();
	printf("eval OK\n");
}
