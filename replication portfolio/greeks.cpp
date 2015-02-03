#include "greeks.h"
#include "underlyings.h"

const deque<float> vect_0;
const deque<deque<float> > vect_00;

// On approxime la dérivée par un taux d'accroissement
// par convention, on prend la première valeur nulle, 
// cela ne pose pas de problème dans la régression grâce au grand nombre de données
deque<float> calculate_delta(deque<float> nav, string ul)
{
	deque<float> delta;
	delta[0] = 0; 
	for (int i = 1; i < nav.size(); i++)
	{
		delta[i]=(nav[i]-nav[i-1])/(ul[i]-ul[i-1]);
	}
	return delta;
}

deque<float> calculate_gamma(deque<float> nav, string ul)
{
	deque<float> gamma;
	deque<float> delta = calculate_delta(nav, ul);
	gamma[0] = 0;
	gamma[1] = 0;
	for (int i = 2; i < nav.size(); i++)
	{
		gamma[i] = (delta[i] - delta[i - 1]) / (ul[i] - ul[i - 1]);
	}
	return gamma;
}

deque<float> calculate_vega(deque<float> nav, string ul)
{
	/*deque<float> vega;
	deque<float> vol;

	vega[0] = 0;
	for (int i = 1; i < nav.size(); i++)
	{
		vega[i] = (nav[i] - nav[i - 1]) / (vol[i] - vol[i - 1]);
	}
	return vega;*/
	return vect_0;
}

deque<float> calculate_rho(deque<float> nav)
{
	return vect_0;
}

deque<float> calculate_theta(deque<float>, int maturity)
{
	return vect_0;
}