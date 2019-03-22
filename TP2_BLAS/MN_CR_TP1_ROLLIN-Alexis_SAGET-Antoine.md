% MN - TP n°2 : BLAS
% Alexis Rollin - Antoine Saget

# `copy`

Pour la fonction `copy`, l'évaluation ne ce fait pas en nombre d'opérations flottantes par secondes puisqu'on fais uniquement des accès et écriture mémoire. On peut cependant calculé le nombre d'octets transferé par secondes. 

| Fonction | Go/s  |
| :------: | :---: |
|  scopy   |  0.7  |
|  dcopy   |  1.4  |
|  ccopy   |  1.4  |
|  zcopy   |  2.5  |

# `nrm2`

Pour la fonction `nrm2` avec les complexes la formule est la suivante pour un vecteur $v$ taille 2 :
$$
nrm2 = \sqrt{\sqrt{v_1.réel^2 + v_1.imaginaire^2}^2 + \sqrt{v_2.réel^2 + v_2.imaginaire^2}^2}
$$

C'est une perte de temps de caluler le carré d'une racine carré. Nous avons donc simplifier le calcul de la manière suivante :

$$
nrm2 = \sqrt{v_1.réel^2 + v_1.imaginaire^2 + v_2.réel^2 + v_2.imaginaire^2}
$$

# `gemv`

# `gemm`

Pour la fonction `gemm` nous avons choisis de ré-utiliser `dot`. On a donc deux boucles imbriquées + une troisième dans l'appel de `dot`. Avant de commencer les calculs on test quelques cas particulier pour éviter les multiplications par `0` ou les ajouts de `0` qui ferais perdre du temps inutilement. 

# Etude de perfomances

Nous avons compilé avec l'option `-O3`. Voici nos résultats en `GFLOP/S`:

|      Type       | axpy  |  dot  | gemv  | gemm  |
| :-------------: | :---: | :---: | :---: | :---: |
|      float      | 0.175 | 0.177 |       | 1.060 |
|     double      | 0.195 | 0.143 |       | 0.429 |
|    complexe     | 1.152 | 1.432 |       | 2.926 |
| complexe double | 1.718 | 1.787 |       | 2.567 |

On constate un nombre d'opérations par secondes plus grand pour les nombres complexes. C'est expliqué par le fait que pour des matrices ou vecteurs de même taille (et donc un nombre d'accès mémoire équivalents), on fais plus d'opérations pour les nombres complexes que pour les réels, donc le temps des accès mémoire est mieux amortis.

On remarque aussi que les opétations vecteurs / matrices sont plus performantes que les opérations vecteurs / vecteurs et que les opérations matrices / matrices sont plus perfomantes que les opétations vecteurs / matrices. Encore une fois, c'est possible car on rentabilise mieux nos accès mémoire : une ligne de matrice va être ré-utiliser plusieurs fois consécutivement.  
