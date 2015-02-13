#pragma once
#include "Vanilla_Products.h"
#include "Portfolio.h"
#include <dataanalysis.h> 
//	Header de la librairie externe, permettant d'importer la classe real_2d_array qui est le format de matrice utilis�e par la fonction de 
//	regresion lin�aire de l'algorithme
using namespace std;

/*	reg_matrix permet de construire la matrice de regression lin�raire qui sera utilis�e � partir de toutes les classes construites 
	jusqu'ici. */

class reg_matrix : public data_frame
{
public:
	void add_product(const data_frame &, string, int begin, int end);
	// Cette m�thode permet de rajouter un produit dont les donn�es sont pr�sentes dans le data_frame en argument dans la matrice de regression,
	// elle est utilis�e dans le constructeur de la classe. Gr�ce aux arguments begin et end on peut r�duire la plage de dates sur la quelle on 
	// effectue la r�gression.
	reg_matrix(const Portfolio& , const Vanilla_Products&, int begin, int end); 
	// La matrice de r�gression est construite � partir du portefeuille et des produits vanilles, les arguments begin et end jouent le m�me r�le 
	// que pr�c�dement
	reg_matrix();
	~reg_matrix();
};

// Une fois le data_frame d�fini, on rajoute une fonction qui permet de convertir _data sous la forme d'un real_2d_array
alglib::real_2d_array convert_matrix(const deque<deque<double> > &);  