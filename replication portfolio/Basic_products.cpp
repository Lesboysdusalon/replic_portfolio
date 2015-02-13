#include "Basic_products.h"

/*	Basic_products contient toutes les informations sur le sous jacent et le Risk Free Asset, défini comme des Financial_Products*/

Basic_products::Basic_products(bool x, string ul, const data_frame &data)
{
	_ul = ul;
	if (x) // Définition du sous jacent comme Financial_product
	{
		_nav = getnav(ul, data);
		deque<double> delta(_nav.size(), 1);
		_delta = delta;
		deque<double> gamma(_nav.size(), 0);
		_gamma = gamma;
		_vega = calculate_vega(_nav, ul, data);
		_theta = calculate_theta(_nav, data);
		_rho = calculate_rho(_nav, data);
	}
	else // Définition du risk free asset comme Financial_product
	{
		deque<double> nav_ul = getnav(ul, data);
		_nav.push_back(1); // On suppose l'investissement initial égal à 1.
		deque<double> libor = getnav("LIBOR 3M USD", data);
		for (size_t i = 1; i < nav_ul.size(); i++)
		{
			_nav.push_back(_nav[i - 1] * exp(libor[i]));
		}
		_delta = calculate_delta(_nav, ul, data);
		_gamma = calculate_gamma(_nav, ul, data);
		_vega = calculate_vega(_nav, ul, data);
		_theta = calculate_theta(_nav, data);
		_rho = calculate_rho(_nav, data);
	}
}

Basic_products::Basic_products()
{
}


Basic_products::~Basic_products()
{
}
