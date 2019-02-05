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

void perf_egalite_polynome(int taille) {
	printf("\n Perf egalite_polynome :\n");
	printf("1. Sans zero\n");
	p_polyf_t p1 = creer_polynome(taille - 1);
	p_polyf_t p2 = creer_polynome(taille - 1);
	init_polynome(p1, VAL);
	init_polynome(p2, VAL + 1);

	p_polycreux_t p1_creux = creer_polynome_creux(taille);
	p_polycreux_t p2_creux = creer_polynome_creux(taille);
	init_polynome_creux(p1_creux, VAL, taille);
	init_polynome_creux(p2_creux, VAL + 1, taille);

	assert(egalite_polynome(p1, p1));
	assert(!egalite_polynome(p1, p2));

	assert(egalite_polynome_creux(p1_creux, p1_creux));
	assert(!egalite_polynome_creux(p1_creux, p2_creux));

	printf("OK\n");

	printf("2. Avec zero\n");

	init_polynome_half_zero(p1, VAL);
	init_polynome_half_zero(p2, VAL + 1);
	init_polynome_creux_half_zero(p1_creux, VAL, taille);
	init_polynome_creux_half_zero(p2_creux, VAL + 1, taille);

	assert(egalite_polynome(p1, p1));
	assert(!egalite_polynome(p1, p2));

	assert(egalite_polynome_creux(p1_creux, p1_creux));
	assert(!egalite_polynome_creux(p1_creux, p2_creux));

	printf("OK\n");
}

void perf_multiplication_scalaire_polynome(int taille) {
	printf("\n Perf multiplication_scalaire_polynome :\n");
	printf("1. Sans zero\n");

	p_polyf_t p1 = creer_polynome(taille - 1);
	p_polyf_t pres = creer_polynome(taille - 1);
	init_polynome(p1, VAL);
	init_polynome(pres, VAL * 2.0);

	p_polycreux_t p1_creux = creer_polynome_creux(taille);
	p_polycreux_t pres_creux = creer_polynome_creux(taille);
	init_polynome_creux(p1_creux, VAL, taille);
	init_polynome_creux(pres_creux, VAL * 2.0, taille);

	unsigned long long start, end;

	start = _rdtsc();
	p1 = multiplication_polynome_scalaire(p1, 2.0);
	end = _rdtsc();
	calcul_flop("\r P", taille, end - start);
	assert(egalite_polynome(p1, pres));

	start = _rdtsc();
	p1_creux = multiplication_polynome_scalaire_creux(p1_creux, 2.0);
	end = _rdtsc();
	calcul_flop("\r C", taille, end - start);
	assert(egalite_polynome_creux(p1_creux, pres_creux));

	printf("OK\n");


	printf("2. Avec zero\n");

	init_polynome_half_zero(p1, VAL);
	init_polynome_half_zero(pres, VAL * 2.0);

	init_polynome_creux_half_zero(p1_creux, VAL, taille);
	init_polynome_creux_half_zero(pres_creux, VAL * 2.0, taille);

	start = _rdtsc();
	p1 = multiplication_polynome_scalaire(p1, 2.0);
	end = _rdtsc();
	calcul_flop("\r P", p1->degre + 1, end - start);
	assert(egalite_polynome(p1, pres));

	start = _rdtsc();
	p1_creux = multiplication_polynome_scalaire_creux(p1_creux, 2.0);
	end = _rdtsc();
	calcul_flop("\r C", p1_creux->nelem, end - start);
	assert(egalite_polynome_creux(p1_creux, pres_creux));
	printf("OK\n");
}

#define NB_TAILLES 5
int main(int argc, char **argv) {
	perf_multiplication_scalaire_polynome(10000);

	// int tailles[NB_TAILLES] = {16, 128, 1024, 4096, 4096 * 4};
	// int i;

	// for (i = 0; i < NB_TAILLES; i++) {
	// 	printf("Taille %d :\n", tailles[i]);
	// 	perf_egalite_polynome(tailles[i]);
	// 	perf_multiplication_scalaire_polynome(tailles[i]);
	// 	printf("\n \n");
	// ecrire_polynome_float_creux(p1_creux);
	// }
}
