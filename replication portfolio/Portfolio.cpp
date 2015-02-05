#include "Portfolio.h"
using namespace std;

Portfolio::Portfolio(deque<double> nav, string ul, int maturity)
{
	_nav = nav;
	_ul = ul;
	_maturity = maturity;
	_delta = calculate_delta(nav, ul);
	_gamma = calculate_gamma(nav, ul);
	_vega = calculate_vega(nav, ul);
	_rho = calculate_rho(nav);
	_theta = calculate_theta(nav, maturity);
}

Portfolio::Portfolio()
{
}


Portfolio::~Portfolio()
{
}