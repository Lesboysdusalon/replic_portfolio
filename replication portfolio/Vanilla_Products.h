#pragma once
#include "Option.h"
#include "Basic_products.h"
using namespace std;

/*	La classe Vanilla_products est de permettre de cr�er un data_frame contenant toutes les donn�es de notre base de produits vanilles, 
	sur la quelle nous allons effectuer la regression. 
	Elle sera compos�e d'options, du sous jacent lui m�me et du risk free asset (issus de la clase Basic_products).*/

class Vanilla_Products : public data_frame // La classe Vanilla_product est construite � partir de la classe data_frame.
{
public: 
	// Les nouveaux membres de cette classe correspondent aux arguments du constructeur, il est important de les stocker comme membre de la classe 
	//	pour faciliter la r�organisation des donn�es dans reg_matrix
	string _ul;
	deque<int> _maturity;
	deque<int> _order;
	deque<double> _strike;
	deque<string> _type;
	Vanilla_Products(string ul, deque<int> maturity, deque<int> order, deque<double> strike, deque<string> type, const data_frame &data);
	Vanilla_Products();
	~Vanilla_Products();
};