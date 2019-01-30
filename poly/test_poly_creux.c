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
	printf("Multiplication : ");
	ecrire_polynome_float(p3);
	p_polycreux_t p4 = addition_polynome(p1, p1);
	printf("Addition : ");
	ecrire_polynome_float(p4);
	assert(egalite_polynome(p3, p4));
}

void test_egalite_polynome() {
	p_polycreux_t p1 = lire_polynome_float("p1c");
	p_polycreux_t p2 = lire_polynome_float("p2c");

	assert(egalite_polynome(p1, p1));
	assert(!egalite_polynome(p1, p2));
}
void test_multiplication_polynome_scalaire() {}
void test_eval_polynome() {}


int main(int argc, char **argv) {
	p_polycreux_t p1, p2, p3;

	if (argc != 3) {
		fprintf(stderr, "deux paramètres (polynomes,fichiers) sont à passer \n");
		exit(-1);
	}
	p1 = lire_polynome_float(argv[1]);
	p2 = lire_polynome_float(argv[2]);

	ecrire_polynome_float(p1);
	ecrire_polynome_float(p2);

	test_egalite_polynome();
	test_addition_polynome();
}
