#include "reg_matrix.h"

// Cette méthode permet de rajouter un produit dont les données sont présentes dans le data_frame en argument dans la matrice de regression.
// Bien que les deux classes soient des data_frame, les données n'y seront pas présentes selon la même organisation : dans le data_frame en argument 
// on trouvera toutes les grecques du produit séparées dans des colonnes différentes, alors que dans reg_matrix elles seront mises bout à bout puisque 
// différentes grecques représentent différentes observations.
void reg_matrix::add_product(const data_frame &d, string product_name, int begin, int end)
{
	deque<double> vect;
	deque<string> greeks = { "_delta", "_gamma", "_vega", "_rho", "_theta" };
	for (size_t i = 0; i < greeks.size(); i++)
	{
		deque<double> data_to_add = getnav(product_name + greeks[i], d);
		for (int j = begin; j < end; j++)
		{
			vect.push_back(data_to_add[j]);
		}
	}
	_data.push_back(vect);
	_label.push_back(product_name);
}

reg_matrix::reg_matrix(const Portfolio &port, const Vanilla_Products &vanilla, int begin, int end)
{
	Vanilla_Products local_data = vanilla; 
	// On copie les données dans un nouveau data_frame local
	// Cette copie ne pose pas de problème au niveau de la complexité algorithmique puisqu'elle n'est exécutée qu'une seule fois dans le programme
	local_data.include_financial_product(port,"Portfolio"); // On rajoute le Portfolio au données locales
	// La suite des instructions permettent de rajouter les produits de local_data dans l'objet construit ici
	this->add_product(local_data, local_data._ul, begin, end);
	this->add_product(local_data, "Risk free asset", begin, end);
	for (size_t o = 0; o < local_data._order.size(); o++)
	{
		for (size_t t = 0; t < local_data._maturity.size(); t++)
		{
			for (size_t k = 0; k < local_data._strike.size(); k++)
			{
				for (size_t l = 0; l < local_data._type.size(); l++)
				{
					// Pour retrouver les differents produits, on réutilise la labélisation des options défini dans Options.ccp
					string local_label = local_data._ul + "_" + local_data._type[l] + "_maturity_" + std::to_string(local_data._maturity[t]) + "_order_" + std::to_string(local_data._order[o]) + "_strike_" + std::to_string(local_data._strike[k]);
					this->add_product(local_data, local_label, begin, end);
				}
			}
		}
	}
	this->add_product(local_data, "Portfolio", begin, end); 
	// On rajoute le Portfolio à la fin car la librairie de régression linéraire 
	// implique que la variable à expliquer soit la dernière colonne de la matrice
}

reg_matrix::reg_matrix()
{
}

reg_matrix::~reg_matrix()
{
}

// Cette fonction permet de convertir les données sous forme de real_2d_array, donc de passer d'une structure de données dynamique
// adaptée à la construction des données à une structure de données statique adaptée à l'utilisation de celles ci.
// Avant d'effectuer cette conversion on élimine toutes les valeurs de type INF ou IND issues des calculs des greecques.
// En effet, le LIBOR étant souvent constant d'un jour à l'autre, de nombreuse valeur de rho n'ont pas de sens, il faut donc les supprimer.

alglib::real_2d_array convert_matrix(const deque<deque<double> > &d)
{
	// La première partie permet de supprimer les données abhérentes
	// Pour cela on a besoin de "transposer" la matrice de données d
	deque<deque<double> > tr_d;
	for (size_t j = 0; j < d[0].size(); j++)
	{
		deque<double> row;
		for (size_t i = 0; i < d.size(); i++)
		{
			row.push_back(d[i][j]);
		}
		tr_d.push_back(row);
	}
	// Une fois la transposition faite, il faut supprimer les colonnes, ie les observations, abhérentes
	for (size_t i = 0; i < tr_d.size(); i++)
	{
		for (size_t j = 0; j < tr_d[0].size(); j++)
		{
			if (isinf(tr_d[i][j]) || isnan(tr_d[i][j]))
			{
				tr_d.erase(tr_d.begin()+i); // On élimine toute la colonne de tr_d, qui correspond à une observation
				break;
			}
		}
	}
	// Maintenant il suffit d'effectuer la conversion, c'est à dire copier les données dans un real_2d_array
	alglib::real_2d_array res;
	res.setlength(tr_d.size(),tr_d[0].size());
	for (size_t i = 0; i < tr_d.size(); i++)
	{
		for (size_t j = 0; j < tr_d[0].size(); j++)
		{
			res(i,j) = tr_d[i][j];
		};
	}
	return res;
}
