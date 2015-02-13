# replic_portfolio

Loic Guillet & Matthieu Martal


## Objectif du Projet

Notre projet a pour objectif de réaliser un algorithme de réplication de portefeuille par les grecques.

Chaque portefeuille Répliqué peut être caractérisé par : 
* sa nav, c'est à dire l'ensemble de ses valeurs sur une plage de temps donnée.
* ses grecques, qui sont calculées à partir de la nav.
L'objectif est de créer un portefeuille Réplicant ayant les mêmes grecques que le portefeuille répliqué.
Ce portefeuille Répliquant contient exclusivement des produits vanilles : options vanilles, le sous-jacent et l'actif sans risque.
Les produits vanilles sont chacun étant caractérisé par :
** son sous-jacent
** sa nav, calculé en effectuant un pricing d'option
** ses grecques, utilisées ensuite pour la régression


## Cadre et Approximations

### Approximations et hypothèses
Dans un souci de simplification, nous avons fait les approximations suivantes :
* Libor = taux d'intérêt sans risque
* VIX = volatilité implicite du S&P500
* dériver en temps discret revient à faire un taux d'accroissement
* un unique sous-jacent.

Ces hypothèses sont réalistes, en particulier en ce qui concerne l'amalgame entre la volatilité des options et le VIX. Le VIX est un indicateur mesurant la volatilité moyenne des actions du S&P.
L'unique sous-jacent considéré est le S&P 500. La structure du programme est conçue pour recevoir éventuellement plusieurs sous-jacents.

### Importation des données, Underlying
Nous avons restreint la période d'étude du 1e janvier 2000 au 31 décembre 2014. Les valeurs sont journalières et ajustées.
Les valeurs du S&P 500, du VIX et du Libor sont réelles. Nous les avons téléchargées sur YahooFinance sous format CSV, puis exportées sous Excel pour construire une base de donnée accessible sous GitHub au format CSV.
Cette base de donnée est ensuite importée sous Visual Studio et convertie en un deque de deque de double. Le fichier Underlying réalise cette conversion.


## Financial_Product

Financial_Product est la classe mère de tous les produits financiers utilisés dans la régression. Les classes Basic_Product, Option et Portfolio héritent de Financial_Product.
Nous nous sommes attachés tout au long de ce projet à coder de la manière la plus propre qui soit, ainsi la structure du code est conçue pour pouvoir accueillir de nouveaux produits.
Chaque produit financier est défini par sa nav et par ses grecques.

### Basic_Product
Cette classe regroupe :
* le sous-jacent
* l'actif sans risque

Ces outils de base sont utilisés dans la régression.

### Option

Les Options sont les principaux produits financiers utilisés dans la réplication du portefeuille.
Elles se caractérisent par leurs grecques et leur nav. Etant donné que les grecques se déduisent de la nav, l'enjeu est donc de pricer l'option.
Les Options se divisent en Calls et en Puts, nous les avons pricés avec la formule de Black Scholes.
Le pricing permet de déterminer la valeur de la position entre l'instant où l'ordre est passé et la maturité de l'Option.

### Portfolio

Le portefeuille est de même défini par sa nav, il peut dépendre de plusieurs sous-jacents.
Nous utilisons principalement cette classe dans le but de tester la régression.
Les grecques du Portfolio sont utilisées dans la régression linéaire.


## Grecques

Les grecques sont des indicateurs calculés en théorie à partir de dérivées partielles. Comme le temps est ici discret, nous avons assimilé ces dérivées à des taux d'accroissement.
Les grecques retenues sont les suivantes :
* delta
* gamma
* vega
* rho
* theta

Les grecques sont calculées à partir de la nav du Financial_Product et de la nav du sous-jacent. 
Les grecques du Portfolio et les grecques des Options qui seront utilisées pour la régression.


## Data_frame

Afin d'accéder facilement aux données, nous avons créé une la classe Data_frame. 
Cette classe est composée d'une table de données et d'un vecteur de labels.
Elle est définie de façon usuelle. Chaque deque a une étiquette, ce qui permet d'accéder facilement au contenu du deque via une fonction de recherche.

### Vanilla_product
Le data_frame Vanilla_product regroupe l'ensemble des données relatives aux produits financiers utilisés comme variables explicatives dans la régression.
Chaque colonne de Vanilla_product correspond à une Option ou à un Basic_Product. Il peut s'agir de la nav du produit ou d'un de ses grecques.
Pour les Options, les labels des colonnes sont normalisés de la forme suivante :
S&P500_call_maturity_31_order_12_strike_1200_delta. 
La colonne ayant ce label contient les valeurs journalières du Delta d'un Call de maturité 31 jours de strike 1200$ dont l'ordre d'achat a été passé au 12e jour de la base de données soit mi-janvier 2000.
Cette labélisation permet de retrouver les données facilement.
Il est possible pour l'utilisateur de définir l'ensemble des Financial_Product utilisés ensuite dans la régression. 


## Régression

Maintenant la base des produits vanilles construite, nous allons chercher à exprimer les grecques du Portfolio comme combinaison linéaire des grecques des produits vanilles construits précédemment.
Il s'agit d'une régression multilinéaire de type MCO.

### Librairie utilisée
Nous avons utilisé une librairie dont vous trouverez les références dans le code ci-joint.
Nous avons intégré la librairie de manière à ce qu'elle compile avec le reste de notre projet.
Cette librairie contient tous les outils nécessaires à la régression linéaire.

### reg_matrix
Une fois le data_frame Vanilla_product construit, nous concaténons Vanilla_product et portfolio et transformons l'objet en matrice.
Nous lui avons donné une forme plus adaptée à la régression linéaire.
Pour cela nous avons mis bout à bout les colonnes des grecques d'une même option. Cet outil est la matrice de régression.
Prenons l'exemple d'un Portfolio répliqué par 100 Options, le sous-jacent, l'actif sans risque et une régression de 3500 jours. 
La reg_matrix aura alors 103 colonnes. 3500x5 lignes.
Il y a une colonne pour le Portfolio, une pour le sous-jacent, une pour l'actif sans risque et une par Option.
Les 3500 premières lignes contiennent les valeurs journalières des deltas des produits financiers.
Les 3500 suivantes contiennent les valeurs journalières des gammas des produits financiers etc.
Chaque ligne de la reg_matrix constitue une observation dans la régression linéaire. 


La régression multilinéaire affecte un coefficient à chaque colonne de la matrice et permet ainsi d'exprimer le Portfolio comme combinaison linéaire des différents produits vanilles.


## Main

Le programme se déroule comme suit :

* Création d'un data_frame data.
* Importation des données cvs téléchargées dans data : S&P500, Libor, VIX
* Création d'un portefeuille de sous-jacent S&P500 et de nav arbitraire
* Création de la base de produits vanilles
* Création de la matrice de régression
* Régression multilinéaire sur les grecques
* Interprétation des résultats à l'aide des labels


## Optimisation de la mémoire

Lors des premières exécutions de la régression sur les grecques, l'algorithme mettait plusieurs minutes à tourner. 
Nous avons donc cherché à optimiser l'usage de la mémoire.
Pour cela nous avons effectué des passages en référence.
A chaque fois qu'une instance d'une classe définie dans le projet est passée en argument d'une fonction, cela est fait par référence de manière à optimiser les temps de calculs.
Après ces modifications, l'algorithme tourne en quelques secondes.

## Critique des résultats




