#pragma once
#include <deque>
#include <vector>
#include <iostream>
#include "greeks.h"
using namespace std;

// La classe portefeuille se caractérise par sa nav et les grecs classiques
class Portfolio
{
public:
	vector<float> _nav;
	vector<string> _ul;
	int _maturity;
	vector<vector<float> > _delta;
	vector<vector<float> > _gamma;
	vector<vector<float> > _vega;
	vector<float> _rho;
	vector<float> _theta;

	Portfolio(vector<float>, vector<string>, int);
	Portfolio();
	~Portfolio();
};