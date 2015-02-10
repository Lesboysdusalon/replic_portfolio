#pragma once
#include <deque>
#include <iostream>
#include "data_frame.h"
using namespace std;

// Les fonctions de calcul de grecques ont pour argument le vecteur de valeur du produit, et en fonction des cas, le sous jacent ou la maturit�

deque<double> calculate_delta(deque<double> nav, string ul); 
deque<double> calculate_gamma(deque<double> nav, string ul);
deque<double> calculate_vega(deque<double> nav, string ul);
deque<double> calculate_rho(deque<double> nav);
deque<double> calculate_theta(deque<double> nav, int maturity);