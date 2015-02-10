#include "Financial_product.h"
#include "greeks.h"




Financial_product::Financial_product(bool x,string ul)
{
	if (x) // Définition du sous jacent comme Financial_product
	{
		_nav = data.getnav(ul);
		deque<double> delta(_nav.size(), 1);
		_delta = delta;
		deque<double> gamma(_nav.size(), 0);
		_gamma = gamma;
		_vega = calculate_vega(_nav, ul);
		// Le theta n'est pas défini pour le sous jacent.
		_rho = calculate_rho(_nav);
	}
	else // Définition du risk free asset comme Financial_product
	{
		deque<double> nav_ul = data.getnav(ul);
		_nav.push_back(1); // On suppose l'investissement initial égal à 1.
		deque<double> libor = data.getnav("LIBOR 3M USD");
		for (size_t i = 1; i < nav_ul.size(); i++)
		{
			_nav.push_back(_nav[i - 1] * exp(libor[i]));
		}
		_delta = calculate_delta(_nav, ul);
		_gamma = calculate_gamma(_nav, ul);
		// Le theta n'est pas défnini pour l'actif sans risque
		_rho = calculate_rho(_nav);
	}
}

Financial_product::Financial_product()
{
}


Financial_product::~Financial_product()
{
}
