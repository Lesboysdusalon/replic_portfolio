#pragma once
#include <deque>
#include <iostream>
#include "data_frame.h"
using namespace std;

/*	Calcul des grecques pour la réplication par les grecques.
	Les fonctions de calcul de grecques ont pour argument le vecteur de valeur du produit, et en fonction des cas, le sous jacent 
	ou la maturité.*/

deque<double> calculate_delta(deque<double> nav, string ul, const data_frame &data);
deque<double> calculate_gamma(deque<double> nav, string ul, const data_frame &data);
deque<double> calculate_vega(deque<double> nav, string ul, const data_frame &data);
deque<double> calculate_rho(deque<double> nav, const data_frame &data);
deque<double> calculate_theta(deque<double> nav, const data_frame &data);