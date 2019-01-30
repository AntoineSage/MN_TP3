typedef struct {
	int degre;
	float coeff;
} paire, *p_paire;

typedef struct {
	int nelem;
	paire *tab_paires;
} polycreux_t, *p_polycreux_t;

p_polycreux_t creer_polynome();

void ajouter_paire(p_polycreux_t p, int degre, int coeff);

p_polycreux_t lire_polynome_float(char *nom_fichier);

void ecrire_polynome_float(p_polycreux_t p);


// A faire
int egalite_polynome(p_polycreux_t p1, p_polycreux_t p2);

p_polycreux_t addition_polynome(p_polycreux_t p1, p_polycreux_t p2);

p_polycreux_t multiplication_polynome_scalaire(p_polycreux_t p, float alpha);

float eval_polynome(p_polycreux_t p, float x);

p_polycreux_t multiplication_polynomes(p_polycreux_t p1, p_polycreux_t p2);

p_polycreux_t puissance_polynome(p_polycreux_t p, int n);

p_polycreux_t composition_polynome(p_polycreux_t p, p_polycreux_t q);