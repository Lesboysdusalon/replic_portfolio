#include "Option.h"
using namespace std;

//Nav d'un call d'option de ul, maturity, strike donnés dont l'ordre est passé à la date order
// Le calcul de sa valeur se fait par formule de BS entre la date order et la maturité, et par actualisation par taux d'escompte des valeurs aux bornes pour le reste.
deque<double> nav_call(string ul, int maturity, int order, double strike)
{
	deque<double> value_call;
	deque<double> value_ul = data.getnav(ul);
	deque<double> libor = data.getnav("LIBOR 3M USD");
	deque<double> vol = data.getnav("vol_"+ul);  // On utilise le VIX comme volatilité implicite du S&P 500
	deque<double> d1;
	deque<double> d2;
	double ST = value_ul[order];
	for (size_t i = 0; i < value_ul.size(); i++)
	{
		d1[i] = pow(vol[i]*sqrt(maturity - i),-1) * ( log(ST*pow(strike,-1)) + (libor[i] + 0,5*vol[i])*(maturity - i));
		d2[i] = d1[i] - vol[i] * sqrt(maturity - i);
	}
	for (int i = order; i < maturity; i++)
	{
		value_call[i] = ST*alglib::normaldistribution(d1[i]) - strike*exp(-libor[i]*(maturity - i))*alglib::normaldistribution(d2[i]); // La fonction de répartition de la loi normale est importée à partir de la librairie lib_reg_lin
	}
	for (int i = 0; i < order ; i++)
	{
		value_call[i] = value_call[order] * exp(-libor[i]*(order - i));
	}
	for (size_t i = maturity; i < value_ul.size(); i++)
	{
		value_call[i] = value_call[maturity] * exp(-libor[i]*(maturity - i));
	}

	/*nav_call[0] = value_ul[0]; //on considère qu'aucun ordre n'est passé aux dates t=0 et t=1 (greeks non définis)
	for (size_t i = 1; i < (order - 1); i++)
	{
		nav_call[i] = value_ul[i];
	}
	if ((order + maturity) < (nav.size()-1))
		for (size_t i = order; i < (order + maturity); i++) //la maturity est définie comme une durée et non comme une date
		{
			if (value_ul[i]>=strike)
				nav_call[i] = value_ul[i] - strike - price;
			if (value_ul[i] < strike)
				nav_call[i] = - price;
		}
		for (size_t i = (order + maturity); i < nav.size(); i++)
		{
			nav_call[i] = nav_call[order + maturity];
		}
	if (order + maturity > nav.size()) // on peut éviter la boucle if en prenant min(order+maturity,nav.size()), mais ça ne marche pas pour une raison inconnue..
		for (size_t i = order; i < nav.size(); i++)
		{
			if (value_ul[i] >= strike)
				nav_call[i] = value_ul[i] - strike - price;
			if (value_ul[i] < strike)
				nav_call[i] = -price;
		}*/
	return value_call;
}

deque<double> nav_put(string ul, int maturity, int order, double strike)
{
	deque<double> value_put;
	deque<double> value_ul = data.getnav(ul);
	deque<double> libor = data.getnav("LIBOR 3M USD");
	deque<double> vol = data.getnav("vol_"+ul); 
	deque<double> d1;
	deque<double> d2;
	double ST = value_ul[order];
	for (size_t i = 0; i < value_ul.size(); i++)
	{
		d1[i] = pow(vol[i] * sqrt(maturity - i), -1) * (log(ST*pow(strike, -1)) + (libor[i] + 0,5 * vol[i])*(maturity - i));
		d2[i] = d1[i] - vol[i] * sqrt(maturity - i);
	}
	for (int i = order; i < maturity; i++)
	{
		value_put[i] = -ST*alglib::normaldistribution(-d1[i]) + strike*exp(-libor[i]*(maturity - i))*alglib::normaldistribution(-d2[i]);
	}
	for (int i = 0; i < order; i++)
	{
		value_put[i] = value_put[order] * exp(-libor[i]*(order - i));
	}
	for (size_t i = maturity; i < value_ul.size(); i++)
	{
		value_put[i] = value_put[maturity] * exp(-libor[i]*(maturity - i));
	}
	return value_put;
}

Option::Option(string ul, int maturity, int order, double strike, string type)
{
	
	_nav = type=="call" ? nav_call(ul, maturity, order, strike) : nav_put(ul, maturity, order, strike); // si x=1, on a un call
	_ul = ul;
	_delta = calculate_delta(_nav, ul);  // Il est discutable de calculer les greeks de cette façon, il aurait aussi été possible de le faire en utilisant les formules analytiques dérivées de la formule de procing de Black Scholes.
	_gamma = calculate_gamma(_nav, ul);
	_vega = calculate_vega(_nav, ul);
	_rho = calculate_rho(_nav);
	_theta = calculate_theta(_nav, maturity);
}

Option::Option()
{
}


Option::~Option()
{
}


