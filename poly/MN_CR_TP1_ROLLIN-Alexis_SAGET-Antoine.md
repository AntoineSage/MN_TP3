% MN - TP n°1 : Polynômes
% Alexis Rollin - Antoine Saget

# 1 - Détails d'implémentation

## Lecture de fichier pour les polynômes creux

Pour la lecture de fichier polynômes creux, on choisit le format suivant : 
```
4
0 2.0
1 0.0
2 3.0
3 4.0
``` 

Le premier entier indique le nombre d'élements puis chaque ligne contient un entier pour le degré et un entier pour le coefficient.

## Le type `p_polycreux_t`

Le type pour les polynomes creux est défini de la manière suivante :
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

Une structure avec un entier `nelem` qui correspond au nombre d'éléments du tableau `tab_paires` qui contient des `paires` elles-mêmes constituées de deux entiers pour le degré et coefficient de chaque monôme.

Nous avons aussi fait le choix d'ordonner le tableau de paires par ordre croissant de degré. Cela permet notamment de faciliter les fonctions d'addition, égalité mais impose certaines contraintes pour maintenir l'ordre.

## L'ajout d'une paire dans un polynôme creux

Pour ajouter une paire dans un polynôme creux on cherche d'abord la position à laquelle la paire doit être placée puis on décale le reste du tableau si nécessaire pour finalement insérer la nouvelle paire.

## La fonction d'égalité pour les polynômes creux

Puisque nos deux polynômes ont leurs paires ordonnées par ordre croissant de degré il suffit d'une simple boucle qui compare les degrés et coefficients de chaque paire à chaque indice: 

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
Sans cette version triée nous aurions été contraints à faire à chaque itération une recherche de la paire de degré équivalent dans l'autre polynôme.

## L'addition de deux polynômes creux

Pour profiter de nos paires ordonnées pour l'addition de deux polynômes creux `p1` et `p2` on commence par créer un nouveau polynôme `p3` ayant pour taille `taille p3 = taille p1 + taille p2`.

Ensuite on ajoute la paire de plus petit degré à `p3` et on passe à la paire suivante. Pour trouver la paire de plus petit degré on compare simplement la paire courante du premier polynôme avec celle du deuxième. Les paires courantes sont déterminées par trois indices (un pour chaque polynôme) initialisés à 0 que l'on incrémente à chaque fois qu'une paire est ajouté dans le polynôme résultat.

Si un degré est présent dans les deux polynômes à la fois on fait la somme des coefficients et on l'ajoute seulement si le coefficient calculé est différent de 0.

Finalement on utilise l'indice de paire courante de `p3` pour déterminer le nombre de paires ajouté au total et on réduit (`realloc` du tableau de paires) la taille du polynôme à ce nombre de paires.

Cette implémentation nous permet de se passer d'une fonction intermédiaire de "compactage" du polynôme. Un autre avantage est de ne pas avoir besoin de rechercher de paires de degré équivalent, en parcourant les polynômes "petit à petit" on tombe automatiquement sur les paires ayants le même degré.

## Multiplication

Pour effectuer la multiplication de deux polynômes pleins p1 et p2, on commence par créer un polynôme de degré deg p1 + deg p2.
On prend soin d'initialiser tous ses coefficients à 0 car plusieurs coefficients avec le même degré sont susceptibles d'apparaître, et il faudra donc procéder à la somme du coefficient actuel à ce degré et des nouveaux coefficients.
Dans la forme, la fonction de multiplication s'apparente à un développement: pour chaque coefficient du polynôme p1, on crée des nouveaux coefficients en le multipliant à tous les coefficients de p2 un par un. Le degré associé à chaque nouveau coefficient est calculé en additionnant le degré du coeff de p1 et le degré du coeff de p2.

## Composition


# 2 - Performances

Pour les performances nous avons étudiés le nombre de `GFLOPS/s` pour les fonctions `addition_polynome`, `multiplication_scalaire_polynome`, `multiplication_polynome` et `composition_polynome` en fonction du degré d'optimisation du compilateur, de la taille des polynômes utilisés, du modèle choisi (creux ou non). Voici quelques tableaux récapitulatifs de ce qu'on nous avons pu remarquer de pertinent :

tableaux / graph / explications

Concernant la consommation mémoire, il est évident qu'elle est inférieure pour l'implémentation creuse que pour l'implémentation non creuse lorsqu'on utilise des polynômes creux.  
Par exemple le polynôme `2X^200` à un coût mémoire de `sizeof(float) * 200 + sizeof(int)` pour l'implémentation non creuse tandis qu'il sera pour les polynômes creux de `sizeof(int) + sizeof(paire)` et `sizeof(paire) = sizeof(int) + sizeof(float)`. 

En général `sizeof(int) = sizeof(float) = 4 octets` donc `200 * 4 + 4 = 804 octets` pour l'implémentation non creuse contre `4 + (4 + 4) = 12 octets` pour l'implémentation creuse.

Cependant pour des polynômes pleins, l'implémentation non creuse est moins coûteuse en mémoire car la structure utilisée est plus légère : un entier par monôme contre deux entiers par monôme pour l'implémentation creuse. Si on refait les même calculs que précedemment pour le polynôme `1 + X + X^2 + X^3` on trouve `1 + 4 = 5 octets` pour l'implémentation non creuse et `1 + (2 * 4) = 9 octets` pour l'implémentation creuse. 

tableau / explications

Comparer des fonctions entre elles
Comparer polynôme / polynôme creux
Comparer en fonctions de la taille du polynôme étudié