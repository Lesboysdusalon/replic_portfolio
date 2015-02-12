#pragma once
#include "greeks.h"
using namespace std;

// La classe portefeuille, h�rit�e de la classe Financial_product, avec un constructeur sp�cifique, permettant de construire tout les donn�es � partir de la nav et du sous jacent, et du data_frame contenant les donn�es d'importation.

class Portfolio : public Financial_product
{
public:
	Portfolio(deque<double>, string, data_frame);
	Portfolio();
	~Portfolio();
};