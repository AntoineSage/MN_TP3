% MN - TP n°1 : Polynômes
% Alexis Rollin - Antoine Saget

# 1 - Détails d'implémentation

## Le type `p_polycreux_t`

Le type pour les polynomes creux est définis de la manière suivante :
```c
typedef struct {
	int degre;
	float coeff;
} paire, *p_paire;

typedef struct {
	int nelem;
	paire *tab_paires;
} polycreux_t, *p_polycreux_t;
```

Une structure avec un entier `nelem` qui correspond au nombre d'éléments du tableau `tab_paires` qui contient des `paires` elles mêmes constituées de deux entiers pour le degré et coefficient de chaque monôme.

Nous avons aussi fais le choix d'ordonner le tableau de paires par ordre croissant de degré. Cela permet notamment de faciliter les fonctions d'addition, égalité mais impose certaines contraintes pour maintenir l'ordre.

## La fonction d'égalité pour les polynômes creux

Puisque nos deux polynômes ont leurs paires ordonnés par ordre croissant de degré il suffit d'une simple boucle qui compare les paires de chaque paires à chaque indice: 

```c
register unsigned int i;
if (p1->nelem != p2->nelem) return 0;
for (i = 0; i < p1->nelem; i++) {
	if (p1->tab_paires[i].coeff != p2->tab_paires[i].coeff ||
		p1->tab_paires[i].degre != p2->tab_paires[i].degre)
		return 0;
}
return 1;
```
Sans cette version trié nous aurions été contraints à faire à chaque itération une recherche de la paire de degré équivalent dans l'autre polynôme.

# 2 - Performances

Pour les performances nous avons étudiés le nombre de `GFLOPS/s` pour chaque fonction implémenté en fonction du degré d'optimisation du processeur, de la taille des polynômes utilisés, du modèle choisis (creux ou non). Voici quelques tableaux récapitulatifs de ce qu'on nous avons pu remarqué de pertinent :

tableaux / graph / explications

Concernant la consommation mémoire il est évident qu'elle est inférieure pour l'implémentation creuse que pour l'implémentation non creuse lorsqu'on utilise des polynômes creux. Cependant pour des polynômes pleins, l'implémentation non creuse est moins coûteuse en mémoire car la structure utilisée est plus légère : un entier par monôme contre deux entiers par monôme pour l'implémentation creuse : 

tableau / explications

Comparer des fonctions entre elles
Comparer polynôme / polynôme creux
Comparer en fonctions de la taille du polynôme étudié