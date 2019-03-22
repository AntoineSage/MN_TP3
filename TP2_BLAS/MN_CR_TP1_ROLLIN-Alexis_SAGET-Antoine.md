% MN - TP n°2 : BLAS
% Alexis Rollin - Antoine Saget

# `copy`

Pour la fonction `copy`, l'évaluation ne se fait pas en nombre d'opérations flottantes par seconde puisqu'on fait uniquement des accès et écriture mémoire. On peut cependant calculer le nombre d'octets trasnferés par secondes. 

| Fonction | Go/s  |
| :------: | :---: |
|  scopy   |  0.7  |
|  dcopy   |  1.4  |
|  ccopy   |  1.4  |
|  zcopy   |  2.5  |

# `gemv`

La fonction gemv est divisée en plusieurs parties selon les valeurs des différens coefficients afin d'optimiser les calculs: par exemple quand alpha ou beta sont nuls, on peut très facilement gagner en efficacité en choisissant de traiter ces cas à part. Le principe général de multiplication d'un matrice M*N par un vecteur colonne de taille N est le suivant: on commence par multiplier un à un les éléments du vecteur Y par le coefficient beta. Puis pour chaque ligne, on effectue le produit scalaire de cette ligne avec le vecteur X multiplié par alpha. Le résultat de chacun de ces produits scalaires est ajouté au bon indice dans le vecteur Y.

# `gemm`

Pour la fonction `gemm` nous avons choisi de ré-utiliser `dot`. On a donc deux boucles imbriquées + une troisième dans l'appel de `dot`. Avant de commencer les calculs on teste quelques cas particuliers pour éviter les multiplications par `0` ou les ajouts de `0` qui feraient perdre du temps inutilement. 

# Etude de perfomances

Nous avons compilé avec l'option `-O3`. Voici nos résultats en `GFLOP/S`:

| Type  | axpy  |  dot  | gemv  | gemm  |
| :---: | :---: | :---: | :---: | :---: | 
| float             |       | 0.177 |       | 1.060 |
| double            |       | 0.143 |       | 0.429 |
| complexe          |       | 1.432 |       | 2.926 |
| complexe double   |       | 1.787 |       | 2.567 |

On constate un nombre d'opérations par secondes plus grand pour les nombres complexes. C'est expliqué par le fait que pour des matrices ou vecteurs de même taille (et donc un nombre d'accès mémoire équivalents), on fait plus d'opérations pour les nombres complexes que pour les réels, donc le temps des accès mémoire est mieux amorti.

On remarque aussi que les opérations vecteurs / matrices sont plus performantes que les opérations vecteurs / vecteurs et que les opérations matrices / matrices sont plus perfomantes que les opétations vecteurs / matrices. 

COMPILER AVEC 02


Les optis de gemm :) (précalcul avant d'entrer dans la boucle)