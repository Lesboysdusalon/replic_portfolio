#include "greeks.h"

// On approxime la dérivée par un taux d'accroissement
// par convention, on prend la première valeur nulle, 
// cela ne pose pas de problème dans la régression puisque elle sera effectuée à partir de la date 2.
deque<double> calculate_delta(deque<double> nav, string ul)
{
	deque<double> delta;
	deque<double> value_ul = data.getnav(ul);
	delta.push_back(0); 
	for (size_t i = 1; i < nav.size(); i++)
	{ 
		delta.push_back((nav[i]-nav[i-1])/(value_ul[i]-value_ul[i-1]));
	}
	return delta;
}

deque<double> calculate_gamma(deque<double> nav, string ul)
{
	deque<double> gamma;
	deque<double> delta = calculate_delta(nav, ul);
	gamma.push_back(0);
	for (size_t i = 1; i < nav.size(); i++)
	{
		gamma.push_back((delta[i] - delta[i - 1]) / (ul[i] - ul[i - 1]));
	}
	return gamma;
}

deque<double> calculate_vega(deque<double> nav, string ul)
{
	deque<double> vega;
	deque<double> vol = data.getnav("vol_"+ul);
	vega.push_back(0);
	for (size_t i = 1; i < nav.size(); i++)
	{
		vega.push_back((nav[i] - nav[i - 1]) / (vol[i] - vol[i - 1]));
	}
	return vega;
}

deque<double> calculate_rho(deque<double> nav)
{
	deque<double> rho;
	deque<double> value_r = data.getnav("LIBOR 3M USD");
	rho.push_back(0);
	for (size_t i = 1; i < nav.size(); i++)
	{
		rho.push_back((nav[i] - nav[i - 1]) / (value_r[i] - value_r[i - 1]));
	}
	return rho;
}

deque<double> calculate_theta(deque<double> nav, int maturity)
{
	deque<double> theta;
	theta.push_back(0);
	for (int i = 1; i < maturity; i++)
	{
		theta.push_back((nav[i] - nav[i - 1]) / (maturity - i));
	}
	return theta;
}