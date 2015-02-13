#pragma once
#include "greeks.h"
using namespace std;

/*	La classe Portfolio est héritée de la classe Financial_product.
	Avec un constructeur spécifique elle permet de construire toutes les données à partir de la nav et du sous jacent, 
	et du data_frame contenant les données d'importation. */

class Portfolio : public Financial_product
{
public:
	Portfolio(deque<double>, string, const data_frame &data);
	Portfolio();
	~Portfolio();
};