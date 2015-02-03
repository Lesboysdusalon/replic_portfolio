#pragma once
#include <deque>
#include <iostream>
using namespace std;

// Les fonctions de calcul de grecques ont pour argument le vecteur de nav de valeurs et le vecteur des underlying,
// Elles renvoient donc une matrice de grecques

deque<float> calculate_delta(deque<float> nav, string ul); 
deque<float> calculate_gamma(deque<float> nav, string ul);
deque<float> calculate_vega(deque<float> nav, string ul);

// Les fonctions suivantes prennent uniquement en argument la nav du sous-jacent 
// Elles renvoient un vecteur de grecques
deque<float> calculate_rho(deque<float>);
deque<float> calculate_theta(deque<float>, int);