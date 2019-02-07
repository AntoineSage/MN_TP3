% MN - TP n°1 : Polynômes
% Alexis Rollin - Antoine Saget

# 1 - Détails d'implémentation

## Lecture de fichier pour les polynômes creux

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

Nous avons aussi fait le choix d'ordonner le tableau de paires par ordre croissant de degré. Cela permet notamment de faciliter les fonctions d'addition, et d'égalité mais impose certaines contraintes pour maintenir l'ordre.

## L'ajout d'une paire dans un polynôme creux

Pour ajouter une paire dans un polynôme creux on cherche d'abord la position à laquelle la paire doit être placée puis on décale le reste du tableau si nécessaire pour finalement insérer la nouvelle paire.

\pagebreak

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

## Multiplication de deux polynômes pleins

Pour effectuer la multiplication de deux polynômes pleins `p1` et `p2`, on commence par créer un polynôme résultat de degré `deg p1 + deg p2`.
On prend soin d'initialiser tous ses coefficients à `0` car plusieurs coefficients avec le même degré sont susceptibles d'apparaître, et il faudra donc procéder à la somme du coefficient actuel à ce degré et des nouveaux coefficients.

Dans la forme, la fonction de multiplication s'apparente à un développement: pour chaque coefficient du polynôme `p1`, on crée des nouveaux coefficients en le multipliant à tous les coefficients de `p2` un par un. Le degré associé à chaque nouveau coefficient est calculé en additionnant le degré du coeff de `p1` et le degré du coeff de `p2`. Et chaque nouveau coefficient `c` de degré `d` est additionné au coefficient de degré `d` du polynôme résultat.

\pagebreak

## Multiplication de deux polynômes creux

Comme, avec les polynômes creux, on se sert du principe de développement. Cependant, cette fois-ci, impossible d'initialiser tous les coefficients à 0. Ainsi, après chaque calcul d'une nouvelle paire degré/coefficient, on se retrouve face à 2 cas:
-Il existe déjà une paire degré/coefficient dans le polynôme résultat avec le même degré: dans ce cas-là on additionne les coefficients.
-Il n'existe pas de paire degré/coefficient dans le polynôme résultat avec le même degré: on ajoute la nouvelle paire dans le polynôme résultat.

## Composition

La compostion de `p` et `q` correspond mathématiquement à:
$$
\sum_{i=0}^{taille p * taille q} coeff i de p1*(p2^degre i de p1)
$$

\pagebreak

# 2 - Performances

Pour les performances nous avons étudiés le nombre de `GFLOPS/s` pour les fonctions `addition_polynome`, `multiplication_scalaire_polynome`, `multiplication_polynome` et `composition_polynome` en fonction du degré d'optimisation du compilateur, de la taille des polynômes utilisés, du modèle choisi (creux ou non). Voici ce qu'on nous avons pu remarquer de pertinent. (a savoir que le PC utilisé pour faire toutes ces études de performances est un Intel Core i5-6200U à 2.30GHz)

## Optimisations du compilateur

Nous avons recompilé le programme avec les options `-O`, `-O0`, `-O2`, `-O3`. Voici nos résultats pour l'implémentation non creuse (en GFLOP/s):

Fonction |`-O0` | `-O`  | `-O2` | `-O3`
:-: | :-: | :-: | :-: | :-:
Addition (16384) | 0.243712 | 0.278220 | 0.425866 | 0.542454
Multiplication (128) | 0.589408 |  0.665052 | 0.781436 | 1.596746
Composition (32) | 0.563159 | 0.692761 | 1.676976 | 1.742801

Il est évident avec de tel résultats que les optimisations à la compilation ont un impact non négligeable. On peut par exemple remarqué 3 fois plus d'opérations flottantes par secondes pour la composition entre la version sans optimisation et la version la plus optimisée.

## Tailles des polynômes

La taille des polynômes va faire varier le nombre d'opération par seconde car pour un polynôme petit le nombre d'opération et donc le temps de ces opérations est négligeable devant le reste de la fonction (accès mémoire, comparaisons, ...). Il est donc plus intéressant de travailler avec de grands polynômes. C'est surtout le cas pour les fonctions avec un nombre linéaire d'opération comme `addition_polynome` ou `multiplication_scalaire_polynome` contrairement au fonctions `multiplication_polynome` et `composition_polynome` qui font rapidement beaucoup d'opérations.

Fonction | 128  | 1024 | 2048 | 16384
:-: | :-: | :-: | :-: | :-:
Addition | 0.003969 | 0.008611 | 0.047611 | 0.216692
Multiplication Scalaire | 0.003169 | 0.029361 | 0.216421 | 0.277001

Fonction | 8 | 16 | 32
:-: | :-: | :-: | :-:
Multiplication | 0.033808 | 0.060676 | 0.520831
Composition | 0.048233 | 0.062286 | 0.474669

## Les fonctions entre elles

Avec les tableaux précédents on remarque qu'on obtient plus d'opérations par seconde pour multiplication et composition que pour addition et multiplication par scalaire. Même en augmentant encore la tailles des polynômes il est difficiles d'obtenir plus de 0.3 GFLOP/s pour la multiplication par un scalaire et pour l'addition (sans optimisation compilateur) tandis qu'on dépasse les 0.5 GFLOP/s avec multiplication.

Pour faire `N` opérations avec la fonction d'addition on a besoin de deux polynôme de degré `N - 1` et pour faire l'addition on feras alors `2 * N` rapattriements de la mémoire centrale vers les registres du processeur ce qui a un coût non négligeable en temps.

Pour faire `N` opération avec la fonction de multiplication il suffit d'un polynôme `p1` de degré `0` et un polynôme `p2` de degré `N - 1`. Lors du développement on va alors ne faire que `1 + N` rapattriements de la mémoire centrale vers les registres du processeur (`1` pour `p1[0]` et `N` pour `p2[i]`).

On a donc fais le même nombre d'opération avec les deux fonctions mais avec deux fois moins d'accès mémoire pour la multiplication.

Au vu des études de performances, la multiplication fait plus d'opérations flottantes par secondes que l'addition. Cela est explicable par une "rentabilisation" du temps de calcul. Dans l'addition, pour chaque p1[i] on effectue une opération `+` avec p2[i]. Il faut aussi prendre en compte le coût en temps CM pour ramener p1[i] et p2[i] de la mémoire centrale dans les caches et registres du processeur/coeur. On fait donc une seule opération dans un temps CM+o(CM) (pour simplifier l'explication, on choisit de négliger le temps de l'opération `+`).
Dans la multiplication, pour chaque p1[i] on effectue une opération `*` avec p2[i], c'est-à-dire N opérations `+`. On fait donc N opérations dans un temps CM+o(CM), légèrement supérieur au temps précédent.
Globalement, on a donc 1/(CM+o(CM)) opération/s pour l'addition et N/(CM+o(CM)) opération/s pour la multiplication.


## Polynômes et polynômes creux

Jusqu'à présent nous n'avons que vus les GFLOP/s des fonctions pour l'implémentation non creuse des polynômes. Voici maintenant un comparatif de quelques fonctions avec l'implémentation creuse :

Fonction | Non creux | Creux
:-: | :-: | :-:
Addition | 0.216692 | 0.054103
Multiplication Scalaire | 0.277001 | 0.133742
Multiplication | 0.520831 | 0.017214
Composition | 0.474669 | 0.002526

On remarque que l'implémentation creuse est généralement plus lente. Cela peut-être expliqué par le fait qu'on manipule une structure de données plus lourde (tableau de float contre tableau de paires int/float). Aussi, l'accès à un monôme d'un certain degré ce fait de manière instantannée avec l'implémentation non creuse, il suffit d'accéder à un indice donné du tableau. Pour l'implémentation creuse il est nécessaire de faire des recherches ce qui est plus lent.

Cependant pour un polynôme creux, l'implémentation non creuse va faire beaucoup d'opération inutiles avec les 0 tandis que l'implémentation creuse ne feras que le nécessaire. Donc même si le nombre d'opérations flottantes par secondes de l'implémentation non creuse seras plus élévé que l'implémentation creuse, il peut arriver, suivant les polynôme qu'on choisis, que l'implémentation creuse soit plus rapide en temps d'exécution.

## Consommation mémoire

Concernant la consommation mémoire, il est évident qu'elle est inférieure pour l'implémentation creuse que pour l'implémentation non creuse lorsqu'on utilise des polynômes creux.  
Par exemple le polynôme `2X^200` à un coût mémoire de `sizeof(float) * 200 + sizeof(int)` pour l'implémentation non creuse tandis qu'il sera pour les polynômes creux de `sizeof(int) + sizeof(paire)` et `sizeof(paire) = sizeof(int) + sizeof(float)`.

En général `sizeof(int) = sizeof(float) = 4 octets` donc `200 * 4 + 4 = 804 octets` pour l'implémentation non creuse contre `4 + (4 + 4) = 12 octets` pour l'implémentation creuse.

Cependant pour des polynômes pleins, l'implémentation non creuse est moins coûteuse en mémoire car la structure utilisée est plus légère : un entier par monôme contre un entier et un flottant par monôme pour l'implémentation creuse. Si on refait les même calculs que précedemment pour le polynôme `1 + X + X^2 + X^3` on trouve `1 + 4 = 5 octets` pour l'implémentation non creuse et `1 + (2 * 4) = 9 octets` pour l'implémentation creuse.
