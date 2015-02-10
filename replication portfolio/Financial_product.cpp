#include "Financial_product.h"
#include "greeks.h"




Financial_product::Financial_product(bool x,string ul)
{
	if (x)
	{
		_nav = data.getnav(ul);
		deque<double> delta(_nav.size(), 1);
		_delta = delta;
		deque<double> gamma(_nav.size(), 0);
		_gamma = gamma;
		_vega = calculate_vega(_nav, ul);
		// Theta n'est pas défini pour le sous jacent.
		_rho = calculate_rho(_nav);
	}
	else
	{
		// Calculer la nav d'un investissement au taux sans risque
	}
}

Financial_product::Financial_product()
{
}


Financial_product::~Financial_product()
{
}
