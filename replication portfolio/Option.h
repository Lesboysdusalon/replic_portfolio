#pragma once
#include <deque>
#include <iostream>
#include "Portfolio.h"
#include <specialfunctions.h>
#include "Financial_product.h"
using namespace std;

/*	Les Options sont un des Financial_products utilis�s pour la r�gression.
	De m�me que Basic_product et Portfolio, Option sert � construire les produits financiers. 
	Cependant le constructeur est diff�rent, puisque cette fois on calcule la nav en fonction des param�tres de l'option, 
	par des formules de pricing de Black Scholes. */


class Option : public Financial_product
{
public:
	Option(string ul, int maturity, int order, double strike, string type, const data_frame &data); // Ce constructeur sert � construire des options vanilles. Ici type d�signe si l'option � construire est un call ou un put, les autres param�tres sont les param�tres de pricing de l'option.
	Option();
	~Option();
};

// Calcule la nav d'un call/d'un puts
deque<double> nav_call(string, int, int, double); 
deque<double> nav_put(string, int, int, double);
