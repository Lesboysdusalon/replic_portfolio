#include "Vanilla_Products.h"

/*	Le constructeur Vanilla_Products permet de construire un deque<double> contenant toutes les nav et les greeks des 
	produits vanilles utilisés ensuite pour la régression.
	Chaque deque pris en argument représente l'ensemble des valeurs possibles pouvant être prises par un produit vanille.
	Par exemple, le deque<int> maturity contient toutes les valeurs possibles de maturité.
	On considère que toutes les combinaisons de maturité, de strike etc. sont possibles.
  */

Vanilla_Products::Vanilla_Products(string ul, deque<int> maturity, deque<int> order, deque<double> strike, deque<string> x)
{
	deque<double> delta;
	deque<double> gamma;
	deque<double> vega;
	deque<double> rho;
	deque<double> theta;
	deque<double> nav;
	_data[0] = data.getnav(ul);
	_label[0] = ul;
	int c = 1;
	for (size_t o = 0; o < order.size(); o++)
	{
		for (size_t t = 0; t < maturity.size(); t++)
		{
			for (size_t k = 0; k < strike.size(); k++)
			{
				for (size_t l = 0; l < x.size(); l++)
				{
					Option Vanilla_Option(ul, maturity[t], order[o], strike[k], x[l]);

					_data[c] = Vanilla_Option._nav;
					_data[c + 1] = Vanilla_Option._delta;
					_data[c + 2] = Vanilla_Option._gamma;
					_data[c + 3] = Vanilla_Option._vega;
					_data[c + 4] = Vanilla_Option._rho;
					_data[c + 5] = Vanilla_Option._theta;
					_label[c] = "_nav";
					_label[c + 1] = "_delta";
					_label[c + 2] = "_gamma";
					_label[c + 3] = "_vega";
					_label[c + 4] = "_rho";
					_label[c + 5] = "_theta";
					for (int j = 0; j < 6; j++)
					{
						_label[c + j] = ul + "_" + x[l] + _label[c + j] + "_maturity_" + std::to_string(t) + "_order_" + std::to_string(o) + "_strike_" + std::to_string(k);
					}
					// ex label : CAC40_call_delta_maturity_31_order_0_strike_10
					c += 6;
					  
				}
			}
		}
	}
}

Vanilla_Products::Vanilla_Products()
{
}


Vanilla_Products::~Vanilla_Products()
{
}

