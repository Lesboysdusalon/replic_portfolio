#pragma once
#include "greeks.h"
using namespace std;

/*	La classe Portfolio est h�rit�e de la classe Financial_product.
	Avec un constructeur sp�cifique elle permet de construire toutes les donn�es � partir de la nav et du sous jacent, 
	et du data_frame contenant les donn�es d'importation. */

class Portfolio : public Financial_product
{
public:
	Portfolio(deque<double>, string, const data_frame &data);
	Portfolio();
	~Portfolio();
};