#pragma once
#include "Vanilla_Products.h"
#include "Portfolio.h"
#include <dataanalysis.h> // Header de la librairie externe, permettant d'importer la classe real_2d_array qui est le format de matrice utilisée par la fonction de regresion linéaire de l'algorithme
using namespace std;

// reg_matrix permet de construire la matrice de regression linéraire qui sera utilisée à partir de toutes les classes construites jusqu'ici.
// Cette matrice contient comme premières colonne les différentes observations des différentes greecques du portefeuille, en effet on considère que chaque grecque représente une nouvelle observation dans le cadre de notre régression

class reg_matrix : public data_frame
{
public:
	void add_product(data_frame, string, int begin, int end); // Cette méthode permet de rajouter un produit dont les données sont présentes dans le data_frame en argument dans la matrice de regression, elle est utilisée dans le constructeur de la classe. Grâce aux arguments begin et end on peut réduire la plage de dates sur la quelle on effectue la regression
	reg_matrix(Portfolio, Vanilla_Products, int begin, int end); // La matrice de regression est construite à partir du portefeuille et des produits vanilles, les arguments begin et end jouent le même rôle que précédement
	reg_matrix();
	~reg_matrix();
};

alglib::real_2d_array convert_matrix(deque<deque<double> >);  // Une fois le data_frame défini, on rajoute une fonction qui permet de convertir _data sous la forme d'un real_2d_array
