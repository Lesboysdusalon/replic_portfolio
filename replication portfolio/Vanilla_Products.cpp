#include "Vanilla_Products.h"

/*	Le constructeur Vanilla_Products permet de construire un deque<double> contenant toutes les nav et les greeks des 
	produits vanilles utilis�s ensuite pour la r�gression.
	Chaque deque pris en argument repr�sente l'ensemble des param�tres de pricing d'une option vanille.
	Par exemple, le deque<int> maturity contient toutes les valeurs possibles de maturit�.
	On consid�re que toutes les combinaisons de maturit�, de strike etc. sont possibles.
	La base de donn�es ainsi construite contiendra un ensemble d'options vanilles, mais aussi le sous jacent et un actif sans risque */


Vanilla_Products::Vanilla_Products(string ul, deque<int> maturity, deque<int> order, deque<double> strike, deque<string> type, data_frame data)
{
	_ul = ul;
	_maturity = maturity;
	_order = order;
	_strike = strike;
	_type = type;
	Basic_products underlying(true, ul, data); // On inclus dans la base de donn�es vanilles, ie l'objet en cours de construction, le sous jacent lui m�me
	Basic_products risk_free_asset(false, ul, data);
	this -> include_financial_product(underlying,ul);
	this -> include_financial_product(risk_free_asset,"Risk free asset");
	// Les boucles suivantes permettent de rajouter � la base de produits vanille toutes les options d�finies par les param�tres du constructeur
	int c = 12; // c repr�sente le nombre de donn�es inscrites dans _data, et dans dans _label
	for (size_t o = 0; o < order.size(); o++)
	{
		for (size_t t = 0; t < maturity.size(); t++)
		{
			for (size_t k = 0; k < strike.size(); k++)
			{
				for (size_t l = 0; l < type.size(); l++)
				{
					Option Vanilla_Option(ul, maturity[t], order[o], strike[k], type[l], data);
					this -> include_financial_product(Vanilla_Option,"");
					for (int j = 0; j < 6; j++)
					{
						_label[c + j] = ul + "_" + type[l] + "_maturity_" + std::to_string(maturity[t]) + "_order_" + std::to_string(order[o]) + "_strike_" + std::to_string(strike[k]) + _label[c + j];
					}
					// ex label : CAC40_call_maturity_31_order_0_strike_10_delta. Cette lab�lisation permet de retrouver les donn�es facilement.
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

