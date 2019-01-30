#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly_creux.h"

#include <x86intrin.h>

p_polycreux_t creer_polynome() {
	p_polycreux_t p;

	// unsigned long long start, end;

	// start = _rdtsc();

	p = (p_polycreux_t)malloc(sizeof(polycreux_t));
	p->nelem = 0;
	// DEFINITION MEMOIRE DU POLYNOME A TRAVAILLER

	// end = _rdtsc();

	// printf("creation polynome: %Ld cycles\n", end - start);

	return p;
}


void ajouter_paire(p_polycreux_t p, int degre, int coeff) {
	paire duo;
	int i = 0;
	int j;
	duo.degre = degre;
	duo.coeff = coeff;
	// Placement de la paire de sorte que le tableau de paire soit trié par degré croissant
	while (p->tab_paires[i].degre < degre) {
		i++;
	}
	// decalage des paires pour inserer la nouvelle paire
	for (j = p->nelem - 1; j >= i; j--) {
		p->tab_paires[j + 1] = p->tab_paires[j];
	}
	// Insertion de la nouvelle paire
	p->tab_paires[i] = duo;
	p->nelem++;
}

p_polycreux_t lire_polynome_float(char* nom_fichier) {
	FILE* f;
	p_polycreux_t p;
	int degre;
	int i;
	float coeff;

	unsigned long long start, end;

	start = _rdtsc();

	f = fopen(nom_fichier, "r");
	if (f == NULL) {
		fprintf(f, "erreur ouverture %s \n", nom_fichier);
		exit(-1);
	}

	fscanf(f, "%d", &degre);
	p = creer_polynome();
	for (i = 0; i <= degre; i++) {
		fscanf(f, "%f", &coeff);
		if (coeff != 0.0) {
			ajouter_paire(p, i, coeff);
		}
	}

	fclose(f);

	end = _rdtsc();

	printf("lire polynome:  %Ld cycles\n", end - start);

	return p;
}

void ecrire_polynome_float(p_polycreux_t p) {
	int i;

	if (p->tab_paires[0].degre == 0) {
		printf("%f", p->tab_paires[0].coeff);
	} else if (p->tab_paires[0].degre == 1) {
		printf("%f X", p->tab_paires[0].coeff);
	}
	if (p->tab_paires[1].degre == 1) {
		printf("+ %f X", p->tab_paires[1].coeff);
	}
	for (i = 2; i <= p->nelem; i++) {
		printf("+ %f X^%d ", p->tab_paires[1].coeff, p->tab_paires[1].degre);
	}

	printf("\n");

	return;
}

// Assume que les polynôme creux sont triées par ordre croissant de degré et ne contiennent pas de
// de degré 0.
int egalite_polynome(p_polycreux_t p1, p_polycreux_t p2) {
	register unsigned int i;
	if (p1->nelem != p2->nelem) return 0;
	for (i = 0; i < p1->nelem; i++) {
		if (p1->tab_paires[i].coeff != p2->tab_paires[i].coeff ||
		    p1->tab_paires[i].degre != p2->tab_paires[i].degre)
			return 0;
	}
	return 1;
}

paire creer_paire(int degree, float coeff) {
	paire tmp;
	tmp.degre = degree;
	tmp.coeff = coeff;
	return tmp;
}

// A tester !!
p_polycreux_t addition_polynome(p_polycreux_t p1, p_polycreux_t p2) {
	p_polycreux_t p3 = creer_polynome(p1->nelem + p2->nelem);

	int nelem = 0;

	int compteur_p1 = 0;
	int compteur_p2 = 0;

	paire* paires_p1 = p1->tab_paires;
	paire* paires_p2 = p2->tab_paires;


	while (compteur_p1 < p1->nelem && compteur_p2 < p2->nelem) {
		if (paires_p1[compteur_p1].degre == paires_p2[compteur_p2].degre) {
			int degre = paires_p1[compteur_p1].degre;
			float coeff = paires_p1[compteur_p1++].coeff + paires_p2[compteur_p2++].coeff;
			if (coeff != 0) {
				p3->tab_paires[nelem++] = creer_paire(degre,
				                                      coeff);  // pas sûr de moi
			}
		} else if (paires_p1[compteur_p1].degre > paires_p2[compteur_p2].degre) {
			p3->tab_paires[nelem++] = paires_p2[compteur_p2++];
		} else {
			p3->tab_paires[nelem++] = paires_p1[compteur_p1++];
		}
	}

	while (compteur_p1 < p1->nelem) {
		p3->tab_paires[nelem] = paires_p1[compteur_p1++];
	}

	while (compteur_p2 < p2->nelem) {
		p3->tab_paires[nelem] = paires_p2[compteur_p2++];
	}

	realloc(p3->tab_paires, sizeof(paire) * nelem);
	return p3;
}

// A tester !!
p_polycreux_t multiplication_polynome_scalaire(p_polycreux_t p, float alpha) {
	p_polycreux_t pres = creer_polynome(p->nelem);
	pres->nelem = p->nelem;

	register unsigned int i;
	for (i = 0; i < p->nelem; i++) {
		pres->tab_paires[i].degre = p->tab_paires[i].degre;
		pres->tab_paires[i].coeff = p->tab_paires[i].coeff * alpha;
	}
}

// A tester !!
float eval_polynome(p_polycreux_t p, float x) {
	float res = 0.0;
	register unsigned int i;
	for (i = 0; i < p->nelem; i++) {
		res += pow(x, p->tab_paires[i].degre) * p->tab_paires[i].coeff;
	}
	return res;
}

p_polycreux_t multiplication_polynomes(p_polycreux_t p1, p_polycreux_t p2);

p_polycreux_t puissance_polynome(p_polycreux_t p, int n);

p_polycreux_t composition_polynome(p_polycreux_t p, p_polycreux_t q);