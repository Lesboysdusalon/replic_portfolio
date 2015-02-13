#include "Option.h"
using namespace std;

/*	Les Options sont un des Financial_products utilisés pour la régression sur les greeks.
	Chaque Option est définie par la nav d'un sous-jacent, une maturité, une date de passage de l'ordre et un strike.
	Dans ce fichier, on effectue le Pricing des options et le calcul de ses greeks.
	Cela permet de définir une Option uniquement par sa nav et ses greeks.*/


//	Pricing d'Option
//	Nav d'un call d'option (puis d'un put) de ul, maturité, strike donnés dont l'ordre evalue_ul[i] est passé à la date order
//	Le calcul de sa valeur se fait par formule de Black Scholes entre la date order et la maturité, et par actualisation par 
//	taux d'escompte des valeurs aux bornes pour le revalue_ul[i]e.

//	Pricing CALL
deque<double> nav_call(string ul, int maturity, int order, double strike, const data_frame &data)
{
	deque<double> value_call;
	deque<double> value_ul = getnav(ul, data);
	deque<double> libor = getnav("LIBOR 3M USD", data);
	deque<double> vol = getnav("vol_"+ul, data);  // On utilise le VIX comme volatilité implicite du S&P 500
	deque<double> d1;
	deque<double> d2;
	// Pricing avec la formule de BS
	for (int i = order; i < maturity; i++)
	{
		d1.push_back(pow(vol[i] * sqrt((maturity - i) / 360.0), -1) * (log(value_ul[i] * pow(strike, -1)) + (libor[i] + 0.5 * pow(vol[i], 2))*((maturity - i) / 360.0)));
		d2.push_back(d1[i] - vol[i] * sqrt((maturity - i) / 360.0));
	}
	for (int i = order; i < maturity; i++)
	{
		value_call.push_back(value_ul[i] * alglib::normaldistribution(d1[i]) - strike*exp(-libor[i] * ((maturity - i) / 360.0))*alglib::normaldistribution(d2[i])); // La fonction de répartition de la loi normale evalue_ul[i] importée à partir de la librairie lib_reg_lin
	}
	// A maturité la valeur est égale au Pay-off
	value_call.push_back(max(value_ul[maturity] - strike, 0.0));
	// Actualisation de la valeur au taux sans risque, lequel est assimilé au libor
	for (int i = order - 1; i >= 0; i--)
	{
		value_call.push_front(value_call[order] * exp(-libor[i] * ((order - i) / 360.0)));
	}
	// Actualisation de la valeur au taux sans risque, lequel est assimilé au libor
	for (size_t i = maturity + 1; i < value_ul.size(); i++)
	{
		value_call.push_back(value_call[maturity] * exp(-libor[i] * ((maturity - i) / 360.0)));
	}
	return value_call;
}
//	Pricing PUT
deque<double> nav_put(string ul, int maturity, int order, double strike, const data_frame &data)
{
	deque<double> value_put;
	deque<double> value_ul = getnav(ul, data);
	deque<double> libor = getnav("LIBOR 3M USD", data);
	deque<double> vol = getnav("vol_"+ul, data); 
	deque<double> d1;
	deque<double> d2;
	for (int i = order; i < maturity; i++)
	{
		d1.push_back(pow(vol[i] * sqrt((maturity - i) / 360.0), -1) * (log(value_ul[i] * pow(strike, -1)) + (libor[i] + 0.5 * pow(vol[i], 2))*((maturity - i) / 360.0)));
		d2.push_back(d1[i] - vol[i] * sqrt((maturity - i) / 360.0));
	}
	// Pricing avec BS
	for (int i = order; i < maturity; i++)
	{
		value_put.push_back(-value_ul[i] * alglib::normaldistribution(-d1[i]) + strike*exp(-libor[i] * ((maturity - i) / 360.0))*alglib::normaldistribution(-d2[i]));
	}
	// A maturité la valeur est égale au Pay-off
	value_put.push_back(max(strike - value_ul[maturity], 0.0));
	// Actualisation de la valeur au taux sans risque, lequel est assimilé au libor
	for (int i = order - 1; i >= 0; i--)
	{
		value_put.push_front(value_put[order] * exp(-libor[i] * ((order - i) / 360.0)));
	}
	// Actualisation de la valeur au taux sans risque, lequel est assimilé au libor
	for (size_t i = maturity + 1; i < value_ul.size(); i++)
	{
		value_put.push_back(value_put[maturity] * exp(-libor[i] * ((maturity - i) / 360.0)));
	}
	return value_put;
}

//	Définition de l'Option par sa nav, son under-lying et ses greeks
Option::Option(string ul, int maturity, int order, double strike, string type, const data_frame &data)
{
	_nav = type=="call" ? nav_call(ul, maturity, order, strike, data) : nav_put(ul, maturity, order, strike, data);
	_ul = ul;
	_delta = calculate_delta(_nav, ul, data);  
//	Il est discutable de calculer les greeks de cette façon, il aurait aussi été possible de le faire en utilisant 
//	les formules analytiques dérivées de la formule de procing de Black Scholes.
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


