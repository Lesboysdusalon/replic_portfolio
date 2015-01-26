#pragma once
#include <vector>
#include <iostream>
using namespace std;

// Les fonctions de calcul de grecques ont pour argument le vecteur de nav de valeurs et le vecteur des underlying,
// Elles renvoient donc une matrice de grecques

vector<vector<float> > calculate_delta(vector<float>, vector<string>); 
vector<vector<float> > calculate_gamma(vector<float>, vector<string>);
vector<vector<float> > calculate_vega(vector<float>, vector<string>);

// Les fonctions suivantes prennent uniquement en argument la nav du sous-jacent 
// Elles renvoient un vecteur de grecques
vector<float> calculate_rho(vector<float>);
vector<float> calculate_theta(vector<float>, int);