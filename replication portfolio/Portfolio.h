#pragma once
#include <deque>
#pragma once
#include <iostream>
#include "greeks.h"
using namespace std;

// La classe portefeuille se caractérise par sa nav et les grecs classiques
class Portfolio
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

	Portfolio(deque<double>, string, int);
	Portfolio();
	~Portfolio();
};