% MN - TP n°2 : BLAS
% Alexis Rollin - Antoine Saget

Nous évoquons dans ce compte-rendu seulement les fonctions pour lesquelles nous avons quelque chose de particulier à mentionner. 

# `copy`

Pour la fonction `copy`, l'évaluation ne se fait pas en nombre d'opérations flottantes par seconde puisqu'on fait uniquement des accès et écriture mémoire. On peut cependant calculer le nombre d'octets transferés par seconde. 

| Fonction | Go/s  | Taille de la structure associé en octets |
| :------: | :---: | :--------------------------------------: |
|  scopy   |  0.7  |                    4                     |
|  dcopy   |  1.4  |                    8                     |
|  ccopy   |  1.4  |                    8                     |
|  zcopy   |  2.5  |                    16                    |

Au vu des résultats nous pouvons émettre l'hypothèse suivante : pour les structures de données que nous avons utilisé, les temps d'accès mémoire sont les mêmes quelque soit la taille de la structure. Ainsi, pour deux structures différentes on aura un temps d'exécution équivalent mais plus d'octets transferés pour la structure la plus grosse. Nous avons d'ailleurs ajouté une colonne `taille de la structure` au tableau pour se rendre compte que pour une structure deux fois plus grosse, on a un transfert deux fois plus rapide.

> Nous n'avons pas fait de tests plus approfondis mais nous supposons que cette augmentation est limitée et que pour une structure trop grande on observera un ralentissement. Sinon cela impliquerait une vitesse de transfert mémoire potentiellement infinie.

Les résultats précédents ont été obtenus sans l'option de compilation `-O3`. Les résultats sont différents avec cette option : 

| Fonction | Go/s  |
| :------: | :---: |
|  scopy   |  3.2  |
|  dcopy   |  6.8  |
|  ccopy   |  5.9  |
|  zcopy   | 10.7  |

On a de bien meilleurs résultats, mais l'évolution du nombre de `Go/s` en fonction de la taille de la structure reste le globalement le même. 

# `nrm2`

Pour la fonction `nrm2` avec les complexes, la formule est la suivante pour un vecteur $v$ taille 2 :
$$
nrm2 = \sqrt{\sqrt{v_1.réel^2 + v_1.imaginaire^2}^2 + \sqrt{v_2.réel^2 + v_2.imaginaire^2}^2}
$$

C'est une perte de temps de caluler le carré d'une racine carré. Nous avons donc simplifié le calcul de la manière suivante :

$$
nrm2 = \sqrt{v_1.réel^2 + v_1.imaginaire^2 + v_2.réel^2 + v_2.imaginaire^2}
$$

# `gemv`

La fonction gemv est divisée en plusieurs parties selon les valeurs des différens coefficients afin d'optimiser les calculs: par exemple quand alpha ou beta sont nuls, on peut très facilement gagner en efficacité en choisissant de traiter ces cas à part. Le principe général de multiplication d'un matrice M*N par un vecteur colonne de taille N est le suivant: on commence par multiplier un à un les éléments du vecteur Y par le coefficient beta. Puis pour chaque ligne, on effectue le produit scalaire de cette ligne avec le vecteur X multiplié par alpha. Le résultat de chacun de ces produits scalaires est ajouté au bon indice dans le vecteur Y.

# `gemm`

Pour la fonction `gemm` nous avons choisi de ré-utiliser `dot`. On a donc deux boucles imbriquées + une troisième dans l'appel de `dot`. Avant de commencer les calculs on teste quelques cas particuliers pour éviter les multiplications par `0` ou les ajouts de `0` qui feraient perdre du temps inutilement. 

# Tests

Nous avons fait de multiples tests pour vérifier le bon fonctionnement de chacune de nos fonctions. Ils sont localisés dans le dossier `tests/`. Il est possible de les compiler avec `make` et d'exécuter tous les tests avec `make tests`.

# Etude de perfomances

Nous avons compilé avec l'option `-O3`. Pour chaque fonction testée nous faisons la moyenne sur $200$ répétitions du même calcul. Il est possible de lancer tous les tests de perfomance grâce à la commande `make perfs` dans le dossier `perf/` .Voici nos résultats en `GFLOP/S`:

|      Type       | axpy  |  dot  | gemv  | gemm  |
| :-------------: | :---: | :---: | :---: | :---: |
|      float      | 0.175 | 0.177 | 0.272 | 1.060 |
|     double      | 0.195 | 0.143 | 0.258 | 0.429 |
|    complexe     | 1.152 | 1.432 | 1.028 | 2.926 |
| complexe double | 1.718 | 1.787 | 1.421 | 2.567 |

On constate un nombre d'opérations par secondes plus grand pour les nombres complexes. C'est expliqué par le fait que pour des matrices ou vecteurs de même taille (et donc un nombre d'accès mémoire équivalents), on fait plus d'opérations pour les nombres complexes que pour les réels, donc le temps des accès mémoire est mieux amorti.

On remarque aussi que les opétations vecteurs / matrices sont plus performantes que les opérations vecteurs / vecteurs et que les opérations matrices / matrices sont plus perfomantes que les opétations vecteurs / matrices. Encore une fois, c'est possible car on rentabilise mieux nos accès mémoire : une ligne de matrice va être ré-utilisée plusieurs fois consécutivement.  
