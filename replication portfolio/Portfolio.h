#pragma once
#include "greeks.h"
using namespace std;

// La classe portefeuille, héritée de la classe Financial_product, avec un constructeur spécifique, permettant de construire tout les données à partir de la nav et du sous jacent, et du data_frame contenant les données d'importation.

class Portfolio : public Financial_product
{
public:
	Portfolio(deque<double>, string, data_frame);
	Portfolio();
	~Portfolio();
};