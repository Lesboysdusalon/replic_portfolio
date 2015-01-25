#include "Portfolio.h"
using namespace std;

Portfolio::Portfolio(vector<float> a, vector<string> b, int c)
{
	nav = a;
	ul = b;
	maturity = c;

	delta = calculate_delta(nav, ul);
	gamma = calculate_gamma(nav, ul);
	vega = calculate_vega(nav, ul);
	rho = calculate_rho(nav);
	theta = calculate_theta(nav, c);
}

Portfolio::Portfolio()
{
}


Portfolio::~Portfolio()
{
}