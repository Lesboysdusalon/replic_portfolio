#include "greeks.h"

/*	Nous avons choisi de r�pliquer le portefeuille par ses grecques.
	Ces fonctions permettent de calculer les diff�rents grecques.
	Elles seront ensuite utilis�es pour calculer les greeks du portefeuille et des diff�rents produits financiers utilis�s
	dans la r�gression. */



//	On approxime la d�riv�e par un taux d'accroissement
//	par convention, on prend la premi�re valeur nulle, 

//	Calcul de Delta
deque<double> calculate_delta(deque<double> nav, string ul, const data_frame &data)
{
	deque<double> delta;
	deque<double> value_ul = getnav(ul, data);
	delta.push_back(0); 
	for (size_t i = 1; i < nav.size(); i++)
	{ 
		delta.push_back((nav[i]-nav[i-1])/(value_ul[i]-value_ul[i-1]));
	}
	return delta;
}

//	Calcul de Gamma
deque<double> calculate_gamma(deque<double> nav, string ul, const data_frame &data)
{
	deque<double> gamma;
	deque<double> value_ul = getnav(ul, data);
	deque<double> delta = calculate_delta(nav, ul, data);
	gamma.push_back(0);
	for (size_t i = 1; i < nav.size(); i++)
	{
		gamma.push_back((delta[i] - delta[i - 1]) / (value_ul[i] - value_ul[i - 1]));
	}
	return gamma;
}

//	Calcul de Vega
deque<double> calculate_vega(deque<double> nav, string ul, const data_frame &data)
{
	deque<double> vega;
	deque<double> vol = getnav("vol_"+ul, data);
	vega.push_back(0);
	for (size_t i = 1; i < nav.size(); i++)
	{
		vega.push_back((nav[i] - nav[i - 1]) / (vol[i] - vol[i - 1]));
	}
	return vega;
}

//	Calcul de Rho
deque<double> calculate_rho(deque<double> nav, const data_frame &data)
{
	deque<double> rho;
	deque<double> value_r = getnav("LIBOR 3M USD", data);
	rho.push_back(0);
	for (size_t i = 1; i < nav.size(); i++)
	{
		rho.push_back((nav[i] - nav[i - 1]) / (value_r[i] - value_r[i - 1]));
	}
	return rho;
}

//	Calcul de Theta
deque<double> calculate_theta(deque<double> nav, const data_frame &data)
{
	deque<double> theta;
	theta.push_back(0);
	for (size_t i = 1; i < nav.size(); i++)
	{
		theta.push_back(nav[i-1] - nav[i]);
	}
	return theta;
}