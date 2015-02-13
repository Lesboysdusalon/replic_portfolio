#pragma once
#include "Option.h"
#include "Basic_products.h"
using namespace std;

/*	La classe Vanilla_products est de permettre de créer un data_frame contenant toute les données de notre base de produits vanilles, 
	sur la quelle nous allons effectuer la regression. 
	Elle sera composée d'options (issues de la classe Option), du sous jacent lui même et du risk free asset (issus de la clase Basic_products).*/

class Vanilla_Products : public data_frame // La classe Vanilla_product est construite à partir de la classe data_frame, on défini uniquement un constructeur supplémentaire
{
public:
	string _ul;  // Les nouveaux membres de cette classe correspondent aux arguments du constructeur, il est important de les stocker comme membre de la classe pour faciliter la réorganisation des données dans reg_matrix
	deque<int> _maturity;
	deque<int> _order;
	deque<double> _strike;
	deque<string> _type;
	Vanilla_Products(string ul, deque<int> maturity, deque<int> order, deque<double> strike, deque<string> type, const data_frame &data);
	Vanilla_Products();
	~Vanilla_Products();
};