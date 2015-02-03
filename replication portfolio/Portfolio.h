#pragma once
#include <deque>
#include <iostream>
#include "greeks.h"
using namespace std;

// La classe portefeuille se caractérise par sa nav et les grecs classiques
class Portfolio
{
public:
	deque<float> _nav;
	string _ul;
	int _maturity;
	deque<float> _delta;
	deque<float> _gamma;
	deque<float> _vega;
	deque<float> _rho;
	deque<float> _theta;

	Portfolio(deque<float>, string, int);
	Portfolio();
	~Portfolio();
};