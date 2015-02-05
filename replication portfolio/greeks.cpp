#include "greeks.h"

const deque<double> vect_0;
const deque<deque<double> > vect_00;

// On approxime la dérivée par un taux d'accroissement
// par convention, on prend la première valeur nulle, 
// cela ne pose pas de problème dans la régression grâce au grand nombre de données
deque<double> calculate_delta(deque<double> nav, string ul)
{
	deque<double> delta;
	deque<double> value_ul = data.getnav(ul);
	delta[0] = 0; 
	for (size_t i = 1; i < nav.size(); i++)
	{
		delta[i]=(nav[i]-nav[i-1])/(value_ul[i]-value_ul[i-1]);
	}
	return delta;
}

deque<double> calculate_gamma(deque<double> nav, string ul)
{
	deque<double> gamma;
	deque<double> delta = calculate_delta(nav, ul);
	gamma[0] = 0;
	gamma[1] = 0;
	for (size_t i = 2; i < nav.size(); i++)
	{
		gamma[i] = (delta[i] - delta[i - 1]) / (ul[i] - ul[i - 1]);
	}
	return gamma;
}

deque<double> calculate_vega(deque<double> nav, string ul)
{
	deque<double> vega;
	string vol_ul = "vol_"+ul;
	deque<double> vol = data.getnav(vol_ul);
	vega[0] = 0;
	for (size_t i = 1; i < nav.size(); i++)
	{
		vega[i] = (nav[i] - nav[i - 1]) / (vol[i] - vol[i - 1]);
	}
	return vega;
}

deque<double> calculate_rho(deque<double> nav)
{
	deque<double> rho;
	deque<double> value_r = data.getnav("LIBOR 3M USD");
	rho[0] = 0;
	for (size_t i = 1; i < nav.size(); i++)
	{
		rho[i] = (nav[i] - nav[i - 1]) / (value_r[i] - value_r[i - 1]);
	}
	return rho;
}

deque<double> calculate_theta(deque<double> nav, int maturity)
{
	deque<double> theta;
	theta[0] = 0;
	for (int i = 1; i < maturity; i++)
	{
		theta[i] = (nav[i] - nav[i - 1]) / (maturity - i);
	}
	return theta;
}