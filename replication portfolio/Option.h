#pragma once
#include <deque>
#include <iostream>
#include "Portfolio.h"
#include <specialfunctions.h>

using namespace std;

// De même que la classe Portfolio, les Options sont définies par leur nav, le sous jacent, la maturité et les greecques, ainsi les classes sont de même type.
// Cependant le constructeur est différent, puisque cette fois on calcule la nav en fonction des paramètres de l'option, par des formules de pricing de Black Scholes.

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
	Option(string ul, int maturity, int order, double strike, string type); // Ce constructeur sert à construire des options vanilles. Ici type désigne si l'option à construire est un call ou un put, les autres paramètres sont les paramètres de pricing de l'option.
	Option();
	~Option();
};

deque<double> nav_call(string, int, int, double);
deque<double> nav_put(string, int, int, double);
