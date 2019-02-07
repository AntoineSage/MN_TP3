#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"
#include "poly_creux.h"

#include <x86intrin.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define VAL 2

extern int compteur_operation_creux;
extern int compteur_operation_non_creux;

static const float duree_cycle = (float)1 / (float)2.3;  // duree du cycle en nano seconde 10^-9

void calcul_flop(char *message, int nb_operations_flottantes, unsigned long long int cycles) {
	printf("%s %d operations %f GFLOP/s\n", message, nb_operations_flottantes,
		   ((float)nb_operations_flottantes) / (((float)cycles) * duree_cycle));
	return;
}

void perf_egalite_polynome(int taille) {
	printf("Perf egalite_polynome :\n");
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

	printf("2. Avec zero\n");

	init_polynome_half_zero(p1, VAL);
	init_polynome_half_zero(p2, VAL + 1);
	init_polynome_creux_half_zero(p1_creux, VAL, taille);
	init_polynome_creux_half_zero(p2_creux, VAL + 1, taille);

	assert(egalite_polynome(p1, p1));
	assert(!egalite_polynome(p1, p2));

	assert(egalite_polynome_creux(p1_creux, p1_creux));
	assert(!egalite_polynome_creux(p1_creux, p2_creux));
}

void perf_addition_polynome(int taille) {
	p_polyf_t p1 = creer_polynome(taille - 1);
	p_polyf_t p2 = creer_polynome(taille - 1);
	p_polyf_t padd1_2 = creer_polynome(taille - 1);
	init_polynome(p1, 2);
	init_polynome(p2, 4);
	init_polynome(padd1_2, 6);

	p_polyf_t p3 = creer_polynome(taille - 1);
	p_polyf_t p4 = creer_polynome(taille - 1);
	p_polyf_t padd3_4 = creer_polynome(taille - 1);
	init_polynome_half_zero(p3, 2);
	init_polynome_half_zero(p4, 3);
	init_polynome_half_zero(padd3_4, 5);

	p_polycreux_t p1c = creer_polynome_creux(taille);
	p_polycreux_t p2c = creer_polynome_creux(taille);
	p_polycreux_t padd1_2c = creer_polynome_creux(taille);
	init_polynome_creux(p1c, 2, taille);
	init_polynome_creux(p2c, 4, taille);
	init_polynome_creux(padd1_2c, 6, taille);

	p_polycreux_t p3c = creer_polynome_creux(taille);
	p_polycreux_t p4c = creer_polynome_creux(taille);
	p_polycreux_t padd3_4c = creer_polynome_creux(taille);
	init_polynome_creux_half_zero(p3c, 2, taille);
	init_polynome_creux_half_zero(p4c, 3, taille);
	init_polynome_creux_half_zero(padd3_4c, 5, taille);

	unsigned long long start, end;

	compteur_operation_non_creux = 0;
	printf("Addition:\n");
	printf("1. Sans zero:\n");
	start = _rdtsc();
	p_polyf_t pres = addition_polynome(p1, p2);
	end = _rdtsc();
	calcul_flop("\t P", compteur_operation_non_creux, end - start);
	assert(egalite_polynome(pres, padd1_2));

	compteur_operation_creux = 0;
	start = _rdtsc();
	p_polycreux_t presc = addition_polynome_creux(p1c, p2c);
	end = _rdtsc();
	calcul_flop("\t C", compteur_operation_creux, end - start);
	assert(egalite_polynome_creux(padd1_2c, presc));

	printf("2. Avec zeros\n");

	compteur_operation_non_creux = 0;
	start = _rdtsc();
	pres = addition_polynome(p3, p4);
	end = _rdtsc();
	calcul_flop("\t P", taille / 2, end - start);
	assert(egalite_polynome(pres, padd3_4));

	compteur_operation_creux = 0;
	start = _rdtsc();
	presc = addition_polynome_creux(p3c, p4c);
	end = _rdtsc();
	calcul_flop("\t C", taille / 2, end - start);
	assert(egalite_polynome_creux(presc, padd3_4c));
}

void perf_multiplication_scalaire_polynome(int taille) {
	printf("Perf multiplication_scalaire_polynome :\n");
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
	calcul_flop("\t P", taille, end - start);
	assert(egalite_polynome(p1, pres));

	start = _rdtsc();
	p1_creux = multiplication_polynome_scalaire_creux(p1_creux, 2.0);
	end = _rdtsc();
	calcul_flop("\t C", taille, end - start);
	assert(egalite_polynome_creux(p1_creux, pres_creux));

	printf("2. Avec zero\n");

	init_polynome_half_zero(p1, VAL);
	init_polynome_half_zero(pres, VAL * 2.0);

	init_polynome_creux_half_zero(p1_creux, VAL, taille);
	init_polynome_creux_half_zero(pres_creux, VAL * 2.0, taille);

	start = _rdtsc();
	p1 = multiplication_polynome_scalaire(p1, 2.0);
	end = _rdtsc();
	calcul_flop("\t P", p1->degre + 1, end - start);
	assert(egalite_polynome(p1, pres));

	start = _rdtsc();
	p1_creux = multiplication_polynome_scalaire_creux(p1_creux, 2.0);
	end = _rdtsc();
	calcul_flop("\t C", p1_creux->nelem, end - start);
	assert(egalite_polynome_creux(p1_creux, pres_creux));
}

void perf_multiplication_polynome(int taille) {
	p_polyf_t p1 = creer_polynome(taille - 1);
	p_polyf_t p2 = creer_polynome(taille - 1);
	init_polynome(p1, 2);
	init_polynome(p2, 4);

	p_polyf_t p3 = creer_polynome(taille - 1);
	p_polyf_t p4 = creer_polynome(taille - 1);
	init_polynome_half_zero(p3, 2);
	init_polynome_half_zero(p4, 3);

	p_polycreux_t p1c = creer_polynome_creux(taille);
	p_polycreux_t p2c = creer_polynome_creux(taille);
	init_polynome_creux(p1c, 2, taille);
	init_polynome_creux(p2c, 4, taille);

	p_polycreux_t p3c = creer_polynome_creux(taille);
	p_polycreux_t p4c = creer_polynome_creux(taille);
	init_polynome_creux_half_zero(p3c, 2, taille);
	init_polynome_creux_half_zero(p4c, 3, taille);

	unsigned long long start, end;

	printf("Multiplication de polynomes:\n");
	printf("1. Sans zero:\n");

	compteur_operation_non_creux = 0;
	start = _rdtsc();
	multiplication_polynomes(p1, p2);
	end = _rdtsc();
	calcul_flop("\t P", compteur_operation_non_creux, end - start);


	compteur_operation_creux = 0;
	start = _rdtsc();
	multiplication_polynomes_creux(p1c, p2c);
	end = _rdtsc();
	calcul_flop("\t C", compteur_operation_creux, end - start);

	printf("2. Avec zeros 0\n");

	compteur_operation_non_creux = 0;
	start = _rdtsc();
	multiplication_polynomes(p3, p4);
	end = _rdtsc();
	calcul_flop("\t P", compteur_operation_non_creux, end - start);

	compteur_operation_creux = 0;
	start = _rdtsc();
	multiplication_polynomes_creux(p3c, p4c);
	end = _rdtsc();
	calcul_flop("\t C", compteur_operation_creux, end - start);
}

void perf_composition_polynome(int taille) {
	p_polyf_t p1 = creer_polynome(taille - 1);
	p_polyf_t p2 = creer_polynome(taille - 1);
	init_polynome(p1, 2);
	init_polynome(p2, 4);

	p_polyf_t p3 = creer_polynome(taille - 1);
	p_polyf_t p4 = creer_polynome(taille - 1);
	init_polynome_half_zero(p3, 2);
	init_polynome_half_zero(p4, 3);

	p_polycreux_t p1c = creer_polynome_creux(taille);
	p_polycreux_t p2c = creer_polynome_creux(taille);
	init_polynome_creux(p1c, 2, taille);
	init_polynome_creux(p2c, 4, taille);

	p_polycreux_t p3c = creer_polynome_creux(taille);
	p_polycreux_t p4c = creer_polynome_creux(taille);
	init_polynome_creux_half_zero(p3c, 2, taille);
	init_polynome_creux_half_zero(p4c, 3, taille);

	unsigned long long start, end;

	printf("Composition de polynomes:\n");
	printf("1. Sans zero:\n");

	compteur_operation_non_creux = 0;
	start = _rdtsc();
	composition_polynome(p1, p2);
	end = _rdtsc();
	calcul_flop("\t P", compteur_operation_non_creux, end - start);


	compteur_operation_creux = 0;
	start = _rdtsc();
	composition_polynome_creux(p1c, p2c);
	end = _rdtsc();
	calcul_flop("\t C", compteur_operation_creux, end - start);

	printf("2. Avec zeros 0\n");

	compteur_operation_non_creux = 0;
	start = _rdtsc();
	composition_polynome(p3, p4);
	end = _rdtsc();
	calcul_flop("\t P", compteur_operation_non_creux, end - start);

	compteur_operation_creux = 0;
	start = _rdtsc();
	composition_polynome_creux(p3c, p4c);
	end = _rdtsc();
	calcul_flop("\t C", compteur_operation_creux, end - start);
}

// Nb d'opérations

void perf_eval_polynome(int taille) {
	printf("\n Perf eval_polynome :\n");
	printf("1. Sans zero\n");

	p_polyf_t p1 = creer_polynome(taille - 1);
	float out;
	float res = taille * 2;
	init_polynome(p1, VAL);

	p_polycreux_t p1_creux = creer_polynome_creux(taille);
	init_polynome_creux(p1_creux, VAL, taille);

	unsigned long long start, end;

	start = _rdtsc();
	out = eval_polynome(p1, 1.0);
	end = _rdtsc();
	calcul_flop("\r P", taille * 2, end - start);
	assert(res == out);

	start = _rdtsc();
	out = eval_polynome_creux(p1_creux, 1.0);  // Pas sûr pour le nb d'opérations
	end = _rdtsc();
	calcul_flop("\r C", taille * 2, end - start);
	assert(res == out);

	printf("OK\n");


	printf("2. Avec zero\n");

	res = ((taille + 1) / 2) * 2;
	init_polynome_half_zero(p1, VAL);
	init_polynome_creux_half_zero(p1_creux, VAL, taille);

	start = _rdtsc();
	out = eval_polynome(p1, 1.0);
	end = _rdtsc();
	calcul_flop("\r P", (p1->degre + 1) * 2, end - start);
	assert(res == out);

	start = _rdtsc();
	out = eval_polynome_creux(p1_creux, 1.0);  // Pas sûr pour le nb d'opérations
	end = _rdtsc();
	calcul_flop("\r C", (p1_creux->nelem) * 2, end - start);
	assert(res == out);
}

#define NB_TAILLES 5
int main(int argc, char **argv) {
	/* int tailles[NB_TAILLES] = {8, 16, 32};
	 int i;

	 for (i = 0; i < NB_TAILLES; i++) {
		 printf("Taille %d :\n", tailles[i]);
		 // perf_egalite_polynome(tailles[i]);
		 // perf_multiplication_scalaire_polynome(tailles[i]);
		 // perf_addition_polynome(tailles[i]);

		 perf_multiplication_polynome(tailles[i]);
		 perf_composition_polynome(tailles[i]);
		 printf("\n \n");
	 } */
	perf_addition_polynome(4096 * 4);
	perf_multiplication_scalaire_polynome(4096 * 4 * 4 * 2);
	perf_multiplication_polynome(128);
	perf_composition_polynome(32);
}
