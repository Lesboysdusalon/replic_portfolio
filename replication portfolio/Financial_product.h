#pragma once
#include <deque>
using namespace std;

// La classe Financial_product permet de donner une structure commune aux différents produits financiers que l'on manipule, elle intègre aussi la création des produits les plus basiques : le sous jacent lui même et l'actif sans risque

class Financial_product
{
public:
	deque<double> _nav;
	string _ul;
	deque<double> _delta;
	deque<double> _gamma;
	deque<double> _vega;
	deque<double> _rho;
	deque<double> _theta;
	Financial_product(bool x, string ul); // La variable booléène permet de créer le sous jacent si x est vraie, et l'actif sans risque sinon.
	Financial_product();
	~Financial_product();
};
