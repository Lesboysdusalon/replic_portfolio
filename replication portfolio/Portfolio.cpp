#include "Portfolio.h"
using namespace std;


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