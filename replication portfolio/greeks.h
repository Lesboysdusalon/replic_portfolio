#pragma once
#include <deque>
#include <iostream>
#include "data_frame.h"
using namespace std;

// Les fonctions de calcul de grecques ont pour argument le vecteur de nav de valeurs et le vecteur des underlying,
// Elles renvoient donc une matrice de grecques

deque<double> calculate_delta(deque<double> nav, string ul); 
deque<double> calculate_gamma(deque<double> nav, string ul);
deque<double> calculate_vega(deque<double> nav, string ul);

// Les fonctions suivantes prennent uniquement en argument la nav du sous-jacent 
// Elles renvoient un vecteur de grecques
deque<double> calculate_rho(deque<double>);
deque<double> calculate_theta(deque<double>, int);