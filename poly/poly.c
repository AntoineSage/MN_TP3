#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

#include <x86intrin.h>

p_polyf_t creer_polynome(int degre) {
	p_polyf_t p;

	// unsigned long long start, end;

	// start = _rdtsc();

	p = (p_polyf_t)malloc(sizeof(polyf_t));
	p->degre = degre;

	p->coeff = (float *)malloc((degre + 1) * sizeof(float));

	// end = _rdtsc();

	// printf("creation polynome: %Ld cycles\n", end - start);

	return p;
}

p_polyf_t lire_polynome_float(char *nom_fichier) {
	FILE *f;
	p_polyf_t p;
	int degre;
	int i;

	unsigned long long start, end;

	start = _rdtsc();

	f = fopen(nom_fichier, "r");
	if (f == NULL) {
		fprintf(f, "erreur ouverture %s \n", nom_fichier);
		exit(-1);
	}

	fscanf(f, "%d", &degre);

	p = creer_polynome(degre);

	for (i = 0; i <= degre; i++) {
		fscanf(f, "%f", &p->coeff[i]);
	}

	fclose(f);

	end = _rdtsc();

	printf("lire polynome:  %Ld cycles\n", end - start);

	return p;
}

void ecrire_polynome_float(p_polyf_t p) {
	int i;

	printf("%f + %f x ", p->coeff[0], p->coeff[1]);

	for (i = 2; i <= p->degre; i++) {
		printf("+ %f X^%d ", p->coeff[i], i);
	}

	printf("\n");

	return;
}

int egalite_polynome(p_polyf_t p1, p_polyf_t p2) {
	if (p1->degre != p2->degre) return 0;

	unsigned register int i;
	for (i = 0; i <= p1->degre; i++) {
		if (p1->coeff[i] != p2->coeff[i]) return 0;
	}

	return 1;
}

p_polyf_t addition_polynome(p_polyf_t p1, p_polyf_t p2) {
	p_polyf_t grand_poly = (p1->degre > p2->degre) ? p1 : p2;
	p_polyf_t petit_poly = (grand_poly == p1) ? p2 : p1;

	p_polyf_t res = creer_polynome(grand_poly->degre);

	register unsigned int i;

	for (i = 0; i <= petit_poly->degre; i++) {
		res->coeff[i] = petit_poly->coeff[i] + grand_poly->coeff[i];
	}

	for (i = petit_poly->degre + 1; i <= grand_poly->degre; i++) {
		res->coeff[i] = grand_poly->coeff[i];
	}

	return res;
}

p_polyf_t multiplication_polynome_scalaire(p_polyf_t p, float alpha) {
	register unsigned int i;
	p_polyf_t res = creer_polynome(p->degre);
	for (i = 0; i <= res->degre; i++) {
		res->coeff[i] = alpha * p->coeff[i];
	}

	return res;
}

// FACTORISATION DE HORNER
float eval_polynome(p_polyf_t p, float x) {
	float res = p->coeff[p->degre];

	register int i;
	for (i = p->degre - 1; i >= 0; i--) {
		res = res * x + p->coeff[i];
	}
	return res;
}

p_polyf_t multiplication_polynomes(p_polyf_t p1, p_polyf_t p2) {
	register unsigned int i, j;
	p_polyf_t p3 = creer_polynome(p1->degre + p2->degre);
	// init de p3
	for (i = 0; i <= p3->degre; i++) {
		p3->coeff[i] = 0;
	}

	for (i = 0; i <= p1->degre; i++) {
		for (j = 0; j <= p2->degre; j++) {
			p3->coeff[i + j] = p3->coeff[i + j] + p1->coeff[i] * p2->coeff[j];
		}
	}

	return p3;
}

p_polyf_t puissance_polynome(p_polyf_t p, int n) {
	if (n == 0) {
		p_polyf_t deg0 = creer_polynome(0);
		deg0->coeff[0] = 1;
		return deg0;
	}

	p_polyf_t res = p;

	register unsigned int i;
	for (i = 0; i < n - 1; i++) {
		res = multiplication_polynomes(res, p);
	}
	return res;
}

p_polyf_t composition_polynome(p_polyf_t p, p_polyf_t q) {
	unsigned int i;
	p_polyf_t res = creer_polynome(p->degre * q->degre);
	// init de res
	for (i = 0; i <= res->degre; i++) {
		res->coeff[i] = 0;
	}

	for (i = 0; i <= p->degre; i++) {
		res = addition_polynome(
		    res, multiplication_polynome_scalaire(puissance_polynome(q, i), (p->coeff[i])));
	}

	return res;
}
