#include "reg_matrix.h"


// Cette fonction permet d'importer un produit financier d'un data_frame � uen matrice de regression.
// Bien que les deux classes soient construites de la m�me fa�on, les donn�es n'y seront pas pr�sentes selon la m�me organisation : dans le data_frame on trouvera toutes les greecques du produit s�par�es dans des colonnes diff�rentes, alors que dans reg_matrix elles seront mises bout � bout puisque diff�rentes grecques repr�sentent diff�rentes observations
void reg_matrix::add_product(data_frame d, string product_name, int begin, int end)
{
	deque<double> vect;
	deque<string> greeks = { "_delta", "_gamma", "_vega", "_rho", "_theta" };
	for (size_t i = 0; i < greeks.size(); i++)
	{
		deque<double> data_to_add = d.getnav(product_name + greeks[i]);
		for (int j = begin; j < end; j++)
		{
			vect.push_back(data_to_add[j]);
		}
	}
	_data.push_back(vect);
	_label.push_back(product_name);
}



reg_matrix::reg_matrix(Portfolio port, Vanilla_Products vanilla, int begin, int end)
{
	Vanilla_Products local_data = vanilla; // On copie les donn�es dans un nouveau data_frame pour expliciter la non modification de vanilla, au niveau machine cela n'est pas n�cessaire puisque l'argument vanilla n'est pas pass� en r�f�rence.
	local_data.include_financial_product(port,"Portfolio"); // On rajoute le Portfolio au donn�es locales
	// La suite des instructions permettent de rajouter les produits de local_data dans le data_frame construit ici
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
					// Pour retrouver les differents produits, on r�utilise la lab�lisation des options d�fini dans Options.ccp
					string local_label = local_data._ul + "_" + local_data._type[l] + "_maturity_" + std::to_string(t) + "_order_" + std::to_string(o) + "_strike_" + std::to_string(k);
					this->add_product(local_data, local_label, begin, end);
				}
			}
		}
	}
	this->add_product(local_data, "Portfolio", begin, end); // On rajoute le Portfolio � la fin car la librairie de r�gression lin�raire implique que la variable � expliquer soit la derni�re colonne de la matrice
}

reg_matrix::reg_matrix()
{
}

reg_matrix::~reg_matrix()
{
}


alglib::real_2d_array convert_matrix(deque<deque<double> > d)
{
	alglib::real_2d_array res;
	res.setlength(d[0].size(), d.size());
	for (size_t i = 0; i < d[0].size(); i++)
	{
		for (size_t j = 0; j < d.size(); j++)
		{
			res[i][j] = d[i][j];
		};
	}
	return res;
}
