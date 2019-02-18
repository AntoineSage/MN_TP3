#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly_creux.h"

#include <x86intrin.h>

int compteur_operation_creux;

p_polycreux_t creer_polynome_creux(int nbre_monomes) {
	p_polycreux_t p;

	p = (p_polycreux_t)malloc(sizeof(polycreux_t));
	p->nelem = 0;
	p->tab_paires = (paire*)malloc((nbre_monomes) * sizeof(paire));

	return p;
}

void ajouter_paire_creux(p_polycreux_t p, int degre, float coeff) {
	if (coeff != 0.0) {
		paire duo;
		int i = 0;
		int j;
		duo.degre = degre;
		duo.coeff = coeff;
		// Placement de la paire de sorte que le tableau de paire soit trié par degré croissant
		while (i < p->nelem && p->tab_paires[i].degre < degre) {
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
}

p_polycreux_t lire_polynome_float_creux(char* nom_fichier) {
	FILE* f;
	p_polycreux_t p;
	int nbre_lignes;
	int i;
	float coeff;
	int degre;

	unsigned long long start, end;

	start = _rdtsc();

	f = fopen(nom_fichier, "r");
	if (f == NULL) {
		fprintf(f, "erreur ouverture %s \n", nom_fichier);
		exit(-1);
	}

	fscanf(f, "%d", &nbre_lignes);
	p = creer_polynome_creux(nbre_lignes);
	for (i = 0; i < nbre_lignes; i++) {
		fscanf(f, "%d", &degre);
		fscanf(f, "%f", &coeff);

		if (coeff != 0.0) {
			ajouter_paire_creux(p, degre, coeff);
		}
	}

	fclose(f);

	end = _rdtsc();

	printf("lire polynome:  %Ld cycles\n", end - start);

	return p;
}

void ecrire_polynome_float_creux(p_polycreux_t p) {
	if (p->nelem > 0) {
		int i;
		if (p->tab_paires[0].degre == 0) {
			printf("%f ", p->tab_paires[0].coeff);
		}

		else if (p->tab_paires[0].degre == 1) {
			printf("%f X ", p->tab_paires[0].coeff);
		}

		else {
			printf("%f X^%d ", p->tab_paires[0].coeff, p->tab_paires[0].degre);
		}

		for (i = 1; i < p->nelem; i++) {
			if (p->tab_paires[i].degre == 1) {
				printf("+ %f X ", p->tab_paires[i].coeff);
			}

			else {
				printf("+ %f X^%d ", p->tab_paires[i].coeff, p->tab_paires[i].degre);
			}
		}
	} else {
		printf("Polynôme nul ");
	}

	printf("\n");

	return;
}

// Assume que les polynôme creux sont triées par ordre croissant de degré et ne contiennent pas de
// de coeff 0.
int egalite_polynome_creux(p_polycreux_t p1, p_polycreux_t p2) {
	register unsigned int i;
	if (p1->nelem != p2->nelem) return 0;
	for (i = 0; i < p1->nelem; i++) {
		if (p1->tab_paires[i].coeff != p2->tab_paires[i].coeff ||
			p1->tab_paires[i].degre != p2->tab_paires[i].degre)
			return 0;
	}
	return 1;
}

paire creer_paire_creux(int degree, float coeff) {
	paire tmp;
	tmp.degre = degree;
	tmp.coeff = coeff;
	return tmp;
}

p_polycreux_t addition_polynome_creux(p_polycreux_t p1, p_polycreux_t p2) {
	p_polycreux_t p3 = creer_polynome_creux(p1->nelem + p2->nelem);

	int nelem = 0;

	int compteur_p1 = 0;
	int compteur_p2 = 0;

	paire* paires_p1 = p1->tab_paires;
	paire* paires_p2 = p2->tab_paires;


	while (compteur_p1 < p1->nelem && compteur_p2 < p2->nelem) {
		if (paires_p1[compteur_p1].degre == paires_p2[compteur_p2].degre) {
			int degre = paires_p1[compteur_p1].degre;
			float coeff = paires_p1[compteur_p1].coeff + paires_p2[compteur_p2].coeff;
			compteur_operation_creux++;
			if (coeff != 0) {
				p3->tab_paires[nelem++] = creer_paire_creux(degre, coeff); 
			}
			compteur_p1++;
			compteur_p2++;
		} else if (paires_p1[compteur_p1].degre > paires_p2[compteur_p2].degre) {
			p3->tab_paires[nelem] = paires_p2[compteur_p2];
			compteur_p2++;
			nelem++;

		} else {
			p3->tab_paires[nelem] = paires_p1[compteur_p1];
			compteur_p1++;
			nelem++;
		}
	}

	while (compteur_p1 < p1->nelem) {
		p3->tab_paires[nelem++] = paires_p1[compteur_p1++];
	}

	while (compteur_p2 < p2->nelem) {
		p3->tab_paires[nelem++] = paires_p2[compteur_p2++];
	}

	p3->tab_paires = realloc(p3->tab_paires, sizeof(paire) * nelem);
	p3->nelem = nelem;

	return p3;
}

p_polycreux_t multiplication_polynome_scalaire_creux(p_polycreux_t p, float alpha) {

	p_polycreux_t pres = creer_polynome_creux(p->nelem);
	pres->nelem = p->nelem;

	if (alpha != 0.0) {
		p_polycreux_t pres = creer_polynome_creux(p->nelem);
		pres->nelem = p->nelem;

		register unsigned int i;
		for (i = 0; i < p->nelem; i++) {
			pres->tab_paires[i].degre = p->tab_paires[i].degre;
			pres->tab_paires[i].coeff = p->tab_paires[i].coeff * alpha;
		}

		return pres;
	} else {
		return creer_polynome_creux(0);
	}
}


float eval_polynome_creux(p_polycreux_t p, float x) {
	float res = 0.0;
	register unsigned int i;
	for (i = 0; i < p->nelem; i++) {
		res += pow(x, p->tab_paires[i].degre) * p->tab_paires[i].coeff;
	}
	return res;
}


p_polycreux_t multiplication_polynomes_creux(p_polycreux_t p1, p_polycreux_t p2) {
	register unsigned int i, j;
	p_polycreux_t p3 = creer_polynome_creux(p1->nelem *p2->nelem);

	int k, l;

	for (i = 0; i < p1->nelem; i++) {
		for (j = 0; j < p2->nelem; j++) {
			k = 0;

			// On cherche la position adequate pour inserer une paire de degre
			// p1->tab_paires[i].degre + p2->tab_paires[j].degre
			while (p1->tab_paires[i].degre + p2->tab_paires[j].degre > p3->tab_paires[k].degre &&
				   k < p3->nelem) {
				k++;
			}

			// Un coeff a deja ce degre, donc il faut additionner les coeffs
			if (p1->tab_paires[i].degre + p2->tab_paires[j].degre == p3->tab_paires[k].degre) {
				p3->tab_paires[k].coeff = p3->tab_paires[k].coeff + p1->tab_paires[i].coeff * p2->tab_paires[j].coeff;
					compteur_operation_creux=compteur_operation_creux+2;
			}
			// Ce degre n'a pas de coeff, il faut creer une nouvelle paire
			else {
				// decalage des paires pour inserer la nouvelle paire
				for (l = p3->nelem - 1; l >= k; l--) {
					p3->tab_paires[l + 1] = p3->tab_paires[l];
				}
				// Insertion de la nouvelle paire
				p3->tab_paires[k].coeff = p1->tab_paires[i].coeff * p2->tab_paires[j].coeff;
				compteur_operation_creux++;
				p3->tab_paires[k].degre = p1->tab_paires[i].degre + p2->tab_paires[j].degre;
				p3->nelem++;
			}
		}
	}
	p3->tab_paires = realloc(p3->tab_paires, sizeof(paire) * p3->nelem);
	return p3;
}

p_polycreux_t puissance_polynome_creux(p_polycreux_t p, int n) {
	if (n == 0) {
		p_polycreux_t deg0 = creer_polynome_creux(1);
		deg0->nelem = 1;
		deg0->tab_paires[0].degre = 0;
		deg0->tab_paires[0].coeff = 1;
		return deg0;
	}

	p_polycreux_t res = p;

	register unsigned int i;
	for (i = 0; i < n - 1; i++) {
		res = multiplication_polynomes_creux(res, p);
	}
	return res;
}

p_polycreux_t composition_polynome_creux(p_polycreux_t p, p_polycreux_t q) {
	unsigned int i;

	p_polycreux_t res = creer_polynome_creux(p->nelem* q->nelem);

	for (i = 0; i < p->nelem; i++) {
		res = addition_polynome_creux(res, multiplication_polynome_scalaire_creux(puissance_polynome_creux(q, i), (p->tab_paires[i].coeff)));
	}

	return res;
}

void detruire_polynome_creux(p_polycreux_t p) {
	free(p->tab_paires);
	free(p);

	return;
}

void init_polynome_creux(p_polycreux_t p, float x, int taille) {
	register unsigned int i;

	p->nelem = 0;

	for (i = 0; i < taille; ++i) {
		ajouter_paire_creux(p, i, x);
	}
}

void init_polynome_creux_half_zero(p_polycreux_t p, float x, int taille) {
	register unsigned int i;

	p->nelem = 0;

	for (i = 0; i < taille / 2; ++i) {
		ajouter_paire_creux(p, i, 0.0);
	}
	for (i = taille / 2; i < taille; ++i) {
		ajouter_paire_creux(p, i, x);
	}

	return;
}
