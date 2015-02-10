#pragma once
#include <deque>
using namespace std;

// La classe Financial_product permet de donner une structure commune aux diff�rents produits financiers que l'on manipule, elle int�gre aussi la cr�ation des produits les plus basiques : le sous jacent lui m�me et l'actif sans risque

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
	Financial_product(bool x, string ul); // La variable bool��ne permet de cr�er le sous jacent si x est vraie, et l'actif sans risque sinon.
	Financial_product();
	~Financial_product();
};
