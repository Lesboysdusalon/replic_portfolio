#pragma once
#include <deque>
#include <iostream>
#include "Portfolio.h"
#include <specialfunctions.h>

using namespace std;

//De même que la classe Portfolio, les Options sont définies par leur nav et leurs grecques
//Il faut juste construire la nav de l'Option en fonction de sa maturité et de l'Ul

class Option
{
public:
	deque<double> _nav;//Construit la nav de l'Option en fonction de la nav de l'Ul et de maturity
	string _ul;
	int _maturity;
	deque<double> _delta;
	deque<double> _gamma;
	deque<double> _vega;
	deque<double> _rho;
	deque<double> _theta;
	Option(string, int, int, double, bool);
	Option();
	~Option();
};

deque<double> nav_call(string, int, int, double);
deque<double> nav_put(string, int, int, double);
