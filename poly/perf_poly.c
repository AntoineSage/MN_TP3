#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"
#include "poly_creux.h"

#include <x86intrin.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define VAL 2

static const float duree_cycle = (float)1 / (float)2.3;  // duree du cycle en nano seconde 10^-9

void calcul_flop(char *message, int nb_operations_flottantes, unsigned long long int cycles) {
	printf("%s %d operations %f GFLOP/s\n", message, nb_operations_flottantes,
		   ((float)nb_operations_flottantes) / (((float)cycles) * duree_cycle));
	return;
}

void perf_egalite_polynome(int taille, int creux) {
	printf("\n Perf egalite_polynome :\n");
	printf("1. Sans zero\n");
	p_polyf_t p1 = creer_polynome(taille - 1);
	p_polyf_t p2 = creer_polynome(taille - 1);
	init_polynome(p1, VAL);
	init_polynome(p2, VAL + 1);

	p_polycreux_t p1_creux = creer_polynome_creux(taille);
	p_polycreux_t p2_creux = creer_polynome_creux(taille);
	init_polynome_creux(p1_creux, VAL);
	init_polynome_creux(p2_creux, VAL + 1);

	assert(egalite_polynome(p1, p1));
	assert(!egalite_polynome(p1, p2));

	assert(egalite_polynome_creux(p1, p2));
	assert(!egalite_polynome_creux(p1, p2));

	printf("OK\n");

	printf("2. Avec zero\n");

	init_polynome_half_zero(p1, VAL);
	init_polynome_half_zero(p2, VAL + 1);
	init_polynome_creux_half_zero(p1_creux, VAL);
	init_polynome_creux_half_zero(p2_creux, VAL + 1);

	assert(egalite_polynome(p1, p1));
	assert(!egalite_polynome(p1, p2));

	assert(egalite_polynome_creux(p1, p1));
	assert(!egalite_polynome_creux(p1, p2));

	printf("OK\n");
}

void perf_multiplication_scalaire_polynome(int taille) {
	printf("\n Perf multiplication_scalaire_polynome :\n");

	p_polyf_t p1 = creer_polynome(taille - 1);
	p_polyf_t pres = creer_polynome(taille - 1);
	init_polynome(p1, VAL);
	init_polynome(pres, VAL * 2.0);

	p_polycreux_t p1_creux = creer_polynome_creux(taille);
	p_polycreux_t pres_creux = creer_polynome_creux(taille);
	init_polynome_creux(p1_creux, VAL);
	init_polynome_creux(pres_creux, VAL * 2.0);

	unsigned long long start, end;

	start = _rdtsc();
	p1 = multiplication_polynome_scalaire(p1, 2.0);
	end = _rdtsc();


	printf("OK\n");
}

int main(int argc, char **argv) {
	p_polyf_t p1, p2, p3, p4, p5, p6;
	unsigned long long start, end;

	if (argc != 3) {
		fprintf(stderr, "deux paramètres (polynomes,fichiers) sont à passer \n");
		exit(-1);
	}

	p1 = lire_polynome_float(argv[1]);
	p2 = lire_polynome_float(argv[2]);

	printf("p1 = ");
	ecrire_polynome_float(p1);

	printf("p2 = ");
	ecrire_polynome_float(p2);

	/*
	  ajouter du code pour tester les fonctions
	  sur les polynomes
	*/

	start = _rdtsc();

	p3 = addition_polynome(p1, p2);

	end = _rdtsc();

	printf("p3 = ");
	ecrire_polynome_float(p3);

	printf("addition %Ld\n", end - start);
	calcul_flop("p1+p2", min(p1->degre, p2->degre) + 1, end - start);
	detruire_polynome(p3);

	p4 = creer_polynome(1024);
	p5 = creer_polynome(1024);

	init_polynome(p4, 1.0);
	init_polynome(p5, 2.0);

	start = _rdtsc();

	p6 = addition_polynome(p4, p5);

	end = _rdtsc();

	printf("addition %Ld\n", end - start);
	calcul_flop("p4+p5", min(p4->degre, p5->degre) + 1, end - start);
	detruire_polynome(p6);
}
