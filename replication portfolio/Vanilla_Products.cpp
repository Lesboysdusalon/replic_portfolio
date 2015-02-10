#include "Vanilla_Products.h"

/*	Le constructeur Vanilla_Products permet de construire un deque<double> contenant toutes les nav et les greeks des 
	produits vanilles utilisés ensuite pour la régression.
	Chaque deque pris en argument représente l'ensemble des paramètres de pricing d'une option vanille.
	Par exemple, le deque<int> maturity contient toutes les valeurs possibles de maturité.
	On considère que toutes les combinaisons de maturité, de strike etc. sont possibles.
	La base de données ainsi construite contiendra un ensemble d'options vanilles, mais aussi le sous jacent et un actif sans risque
  */

Vanilla_Products::Vanilla_Products(string ul, deque<int> maturity, deque<int> order, deque<double> strike, deque<string> x)
{
	deque<double> delta;
	deque<double> gamma;
	deque<double> vega;
	deque<double> rho;
	deque<double> theta;
	deque<double> nav;
	_data.push_back(data.getnav(ul)); // On inclus dans la base de données vanilles, ie l'objet en cours de construction, le sous jacent lui même
	_label.push_back(ul);
	// Les boucles suivantes permettent de rajouter à la base de produits vanille toutes les options définies par les paramètres du constructeur
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
					_data.push_back(Vanilla_Option._nav);
					_data.push_back(Vanilla_Option._delta);
					_data.push_back(Vanilla_Option._gamma);
					_data.push_back(Vanilla_Option._vega);
					_data.push_back(Vanilla_Option._rho);
					_data.push_back(Vanilla_Option._theta);
					_label.push_back("_nav");
					_label.push_back("_delta");
					_label.push_back("_gamma");
					_label.push_back("_vega");
					_label.push_back("_rho");
					_label.push_back("_theta");
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

