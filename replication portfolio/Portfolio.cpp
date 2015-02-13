#include "Portfolio.h"
using namespace std;

/*	La classe portfolio contient la nav, l'under-lying et les grecques du portefeuille à répliquer 
	Nous avons choisi de répliquer le portefeuille par ses greeks.*/

Portfolio::Portfolio(deque<double> nav, string ul, const data_frame &data)
{
	_nav = nav;
	_ul = ul;
	_delta = calculate_delta(nav, ul, data);
	_gamma = calculate_gamma(nav, ul, data);
	_vega = calculate_vega(nav, ul, data);
	_rho = calculate_rho(nav, data);
	_theta = calculate_theta(nav, data);
}

Portfolio::Portfolio()
{
}


Portfolio::~Portfolio()
{
}