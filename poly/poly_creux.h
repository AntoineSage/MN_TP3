typedef struct {
  int degre;
  float coeff;
} paire, *p_paire;

typedef struct {
	int nelem;
	paire *tab_paires;
} polycreux_t, *p_polycreux_t;

p_polycreux_t creer_polynome () ;

void ajouter_paire(p_polycreux_t p, int degre, int coeff);

p_polycreux_t lire_polynome_float (char *nom_fichier) ;

void ecrire_polynome_float (p_polycreux_t p) ;

