# replic_portfolio

Nouvelles modifs à faire : 

Effectuer la régression à la date 2, pour éviter le fait que les grecques sont toujours nulles à t=t_0

Attention : lors de la construction de la matrice de régression, penser à supprimer les valeurs manquantes, ie les valeurs de greeks égales à +/-INF, ou IND.

Modif du theta : il est maintenant indep de la maturité pour qu'il fasse sens dans la regression. La formule vient de la formule wikipédia.

Possibilité amelioration des résultats : calculer les grecques des options grâce à la formule analytique plutôt que par taux de variation.

remplacer la structure de data_frame par une structure de dictionnaire, cela est bien plus adapté. Mais cela demande de recoder masse de trucs.

passer tout les arguments de type data_frame ou autres structures de données lourdes en référence pour limiter les temps de calculs.

checker les begin/end problèmes d'indices dans Vanilla_product.cpp

Problème de pricing des options

A écrire dans le readme final, dans une partie du genre "notes générales sur la prog" : à chaque fois qu'une instance d'une classe défini dans le projet est passée en argument d'une fonction, cela est fait par référence constante de manière à optimiser les temps de calculs.