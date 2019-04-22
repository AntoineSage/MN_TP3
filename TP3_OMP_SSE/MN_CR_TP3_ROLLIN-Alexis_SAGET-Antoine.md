% MN - TP n°2 : BLAS
% Alexis Rollin - Antoine Saget

Pour la pluspart des fonctions utilisant `incX` et `incY` nous avons considéré `incX = incY` pour la parralélisation et `incX = incY = 1` pour la vectorisation.

Le processeur utilisé est un `Intel(R) Core(TM) i5-6200U CPU` à `2.30GHz` composé de `2` coeurs et `4` threads.

# `copy`

La fonction de copie est tellement rapide (même sur de grands vecteurs) qu'il est difficile d'observer des résultats constant entre les différentes exécutions même en faisant la moyenne de 1000 exécutions.

Nous avons malgré tout pu faire des observations intéressantes.  
Nombre de `Go` transferé par seconde pour des vecteurs de taille `4096` :

|       | Pas de parralélisation | 1 thread | 2 thread | 4 thread |
| :---: | :--------------------: | :------: | :------: | :------: |
| scopy |          1.05          |   0.81   |   3.28   |   0.32   |
| dcopy |          6.19          |   4.02   |   8.37   |   1.09   |
| ccopy |          7.80          |   6.15   |   9.43   |   1.17   |
| zcopy |         16.56          |   14.3   |  15.19   |  11.81   |

On peut constater une baisse entre pas de parralélisation et la parralélisation a 1 thread, cela est expliqué par le coût de la parralélisation ajouté par OpenMP, ce coût seras amortis dès que l'on utilise plus d'un thread et que l'on parrallélise vraiment. On ne dépasse que légèrement les performances sans parralélisation en utilisant 2 threads, et a 4 threads, les performances chutent...

On s'intéresse maintenant à la vectorisation. Pour cette fonction nous avons utilisé les instructions `AVX` sur 256 octets. Pour pouvoir facilement comparer la vectorisation avec le reste, chaque fonction BLAS `f()` a une fonction vectorisé `f_V()` associée.  

Pour la vectorisation des fonctions complexes, nous utilisons une structure contenant le nombre réel et le nombre imaginaire. Les fonctions AVX intrinsic d'Intel ne fonctionne pas avec des structures de données. Mais, en mémoire, un tableau de complexe flottants de taille 8 ce comporte exactement comme un tableau de flottants de taille 16, c'est en sachant cela que nous avons pu utilisé les fonctions AVX pour notre strucuture.

Nombre de `Go` transferé par seconde pour des vecteurs de taille `4096` :

|       | Pas de vectorisation | Vectorisation | Vectorisation et parralélisation 2 threads |
| :---: | :------------------: | :-----------: | :----------------------------------------: |
| scopy |         1.05         |     6.07      |                    3.01                    |
| dcopy |         6.19         |     12.60     |                    9.38                    |
| ccopy |         7.80         |     11.89     |                   10.95                    |
| zcopy |        16.56         |     18.14     |                   10.77                    |

On observe une nette amélioration avec l'ajout de vectorisation. Cependant les performances lorsqu'on combine vectorisation et parralélisation sont moins bonnes, c'est un résultat que nous n'avons pas su expliqué.

# `dot`

