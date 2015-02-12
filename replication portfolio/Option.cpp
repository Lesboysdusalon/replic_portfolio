#include "Option.h"
using namespace std;

//Nav d'un call d'option de ul, maturity, strike donnés dont l'ordre evalue_ul[i] passé à la date order
// Le calcul de sa valeur se fait par formule de BS entre la date order et la maturité, et par actualisation par taux d'escompte des valeurs aux bornes pour le revalue_ul[i]e.
deque<double> nav_call(string ul, int maturity, int order, double strike, data_frame data)
{
	deque<double> value_call;
	deque<double> value_ul = data.getnav(ul);
	deque<double> libor = data.getnav("LIBOR 3M USD");
	deque<double> vol = data.getnav("vol_"+ul);  // On utilise le VIX comme volatilité implicite du S&P 500
	deque<double> d1;
	deque<double> d2;
	int low_border = max(order, 0);
	int high_border = min(0, 0);
	for (size_t i = 0; i < value_ul.size(); i++)
	{
		d1.push_back(pow(vol[i]*sqrt(maturity - i),-1) * ( log(value_ul[i]*pow(strike,-1)) + (libor[i] + 0,5*vol[i])*(maturity - i)));
		d2.push_back(d1[i] - vol[i] * sqrt(maturity - i));
	}
	for (int i = order; i < maturity; i++)
	{
		value_call.push_back(value_ul[i]*alglib::normaldistribution(d1[i]) - strike*exp(-libor[i]*(maturity - i))*alglib::normaldistribution(d2[i])); // La fonction de répartition de la loi normale evalue_ul[i] importée à partir de la librairie lib_reg_lin
	}
	value_call.push_back(max(value_ul[maturity] - strike, 0.0));
	for (int i = order - 1; i >= 0; i--)
	{
		value_call.push_front(value_call[order] * exp(-libor[i] * (order - i)));
	}
	for (size_t i = maturity + 1; i < value_ul.size(); i++)
	{
		value_call.push_back(value_call[maturity] * exp(-libor[i]*(maturity - i)));
	}
	return value_call;
}

deque<double> nav_put(string ul, int maturity, int order, double strike, data_frame data)
{
	deque<double> value_put;
	deque<double> value_ul = data.getnav(ul);
	deque<double> libor = data.getnav("LIBOR 3M USD");
	deque<double> vol = data.getnav("vol_"+ul); 
	deque<double> d1;
	deque<double> d2;
	for (size_t i = 0; i < value_ul.size(); i++)
	{
		d1.push_back(pow(vol[i] * sqrt(maturity - i), -1) * (log(value_ul[i]*pow(strike, -1)) + (libor[i] + 0,5 * vol[i])*(maturity - i)));
		d2.push_back(d1[i] - vol[i] * sqrt(maturity - i));
	}
	for (int i = order; i < maturity; i++)
	{
		value_put.push_back(-value_ul[i]*alglib::normaldistribution(-d1[i]) + strike*exp(-libor[i]*(maturity - i))*alglib::normaldistribution(-d2[i]));
	}
	value_put.push_back(max(strike - value_ul[maturity], 0.0));
	for (int i = order - 1; i >= 0; i--)
	{
		value_put.push_front(value_put[order] * exp(-libor[i] * (order - i)));
	}
	for (size_t i = maturity + 1; i < value_ul.size(); i++)
	{
		value_put.push_back(value_put[maturity] * exp(-libor[i]*(maturity - i)));
	}
	return value_put;
}

Option::Option(string ul, int maturity, int order, double strike, string type, data_frame data)
{
	_nav = type=="call" ? nav_call(ul, maturity, order, strike, data) : nav_put(ul, maturity, order, strike, data);
	_ul = ul;
	_delta = calculate_delta(_nav, ul, data);  // Il est discutable de calculer les greeks de cette façon, il aurait aussi été possible de le faire en utilisant les formules analytiques dérivées de la formule de procing de Black Scholes.
	_gamma = calculate_gamma(_nav, ul, data);
	_vega = calculate_vega(_nav, ul, data);
	_rho = calculate_rho(_nav, data);
	_theta = calculate_theta(_nav, data);
}

Option::Option()
{
}


Option::~Option()
{
}


