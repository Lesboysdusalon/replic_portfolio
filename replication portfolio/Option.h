#pragma once
#include <deque>
#include <iostream>
#include "Portfolio.h"
#include <specialfunctions.h>

using namespace std;

// De m�me que la classe Portfolio, les Options sont d�finies par leur nav, le sous jacent, la maturit� et les greecques, ainsi les classes sont de m�me type.
// Cependant le constructeur est diff�rent, puisque cette fois on calcule la nav en fonction des param�tres de l'option, par des formules de pricing de Black Scholes.

class Option
{
public:
	deque<double> _nav;
	string _ul;
	int _maturity;
	deque<double> _delta;
	deque<double> _gamma;
	deque<double> _vega;
	deque<double> _rho;
	deque<double> _theta;
	Option(string ul, int maturity, int order, double strike, string type); // Ce constructeur sert � construire des options vanilles. Ici type d�signe si l'option � construire est un call ou un put, les autres param�tres sont les param�tres de pricing de l'option.
	Option();
	~Option();
};

deque<double> nav_call(string, int, int, double);
deque<double> nav_put(string, int, int, double);
