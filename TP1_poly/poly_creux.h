typedef struct {
	int degre;
	float coeff;
} paire, *p_paire;

typedef struct {
	int nelem;
	paire *tab_paires;
} polycreux_t, *p_polycreux_t;

p_polycreux_t creer_polynome_creux (int nbre_monomes);

void ajouter_paire_creux(p_polycreux_t p, int degre, float coeff);

p_polycreux_t lire_polynome_float_creux(char *nom_fichier);

void ecrire_polynome_float_creux(p_polycreux_t p);

int egalite_polynome_creux(p_polycreux_t p1, p_polycreux_t p2);

paire creer_paire_creux(int degree, float coeff);

p_polycreux_t addition_polynome_creux(p_polycreux_t p1, p_polycreux_t p2);

p_polycreux_t multiplication_polynome_scalaire_creux(p_polycreux_t p, float alpha);

float eval_polynome_creux(p_polycreux_t p, float x);

p_polycreux_t multiplication_polynomes_creux(p_polycreux_t p1, p_polycreux_t p2);

p_polycreux_t puissance_polynome_creux(p_polycreux_t p, int n);

p_polycreux_t composition_polynome_creux(p_polycreux_t p, p_polycreux_t q);

void detruire_polynome_creux(p_polycreux_t p);

void init_polynome_creux(p_polycreux_t p, float x, int taille);

void init_polynome_creux_half_zero(p_polycreux_t p, float x, int taille);

