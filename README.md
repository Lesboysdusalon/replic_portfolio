# replic_portfolio

Nouvelles modifs à faire : 
Effectuer la régression à la date 2, pour éviter le fait que les grecques sont toujours nulles à t=t_0
Attention : lors de la construction de la matrice de régression, penser à supprimer les valeurs manquantes, ie les valeurs de greeks égales à +/-INF, ou IND.
Modif du theta : il est maintenant indep de la maturité pour qu'il fasse sens dans la regression. La formule vient de la formule wikipédia.
Possibilité d'ammeillioration des résultats : calculer les grecques des options grâce à la formule analytique plutôt que par taux de variation.

IMPORTANT : remplacer la structure de data_frame par une structure de dictionnaire, cela est bien plus adapté. Mais cela demande de recoder masse de trucs.
