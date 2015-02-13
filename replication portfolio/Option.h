#pragma once
#include <deque>
#include <iostream>
#include "Portfolio.h"
#include <specialfunctions.h>
#include "Financial_product.h"
using namespace std;

/*	Les Options sont un des Financial_products utilisés pour la régression sur les greeks.
	De même que Basic_product et Portfolio, Option sert à construire les produits financiers. A ne pas confondre avec Vanilla_products
	qui sert à stocker toutes les données dans un data_frame.
	De même que la classe Portfolio, les Options sont définies par leur nav, le sous jacent, la maturité et les grecques, 
	ainsi les classes sont de même type.
	Cependant le constructeur est différent, puisque cette fois on calcule la nav en fonction des paramètres de l'option, 
	par des formules de pricing de Black Scholes. */


class Option : public Financial_product
{
public:
	Option(string ul, int maturity, int order, double strike, string type, const data_frame &data); // Ce constructeur sert à construire des options vanilles. Ici type désigne si l'option à construire est un call ou un put, les autres paramètres sont les paramètres de pricing de l'option.
	Option();
	~Option();
};

deque<double> nav_call(string, int, int, double);
deque<double> nav_put(string, int, int, double);
