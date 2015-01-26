#pragma once
#include <vector>
#include <iostream>
#include "greeks.h"
using namespace std;

// La classe portefeuille se caractérise par sa nav et les grecs classiques
class Portfolio
{
public:
	vector<float> nav;
	vector<string> ul;
	int maturity;
	vector<vector<float> > delta;
	vector<vector<float> > gamma;
	vector<vector<float> > vega;
	vector<float> rho;
	vector<float> theta;

	Portfolio(vector<float>, vector<string>, int);
	Portfolio();
	~Portfolio();
};