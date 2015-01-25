#pragma once
#include <vector>
#include <iostream>
using namespace std;

vector<vector<float> > calculate_delta(vector<float>, vector<string>);
vector<vector<float> > calculate_gamma(vector<float>, vector<string>);
vector<vector<float> > calculate_vega(vector<float>, vector<string>);
vector<float> calculate_rho(vector<float>);
vector<float> calculate_theta(vector<float>, int);