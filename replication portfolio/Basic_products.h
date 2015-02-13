#pragma once
#include "data_frame.h"
#include "greeks.h"

/*	Cette classe défini les produits de base : le sous jacent lui même et l'actif sans risque.
	La structure du programme est prévue pour accueillir plusieurs sous-jacents.
	Ainsi, on pourrait complexifier le projet en prenant en compte plusieurs sous-jacents sans rien modifier par ailleurs.
	Basic_products est hérité de Financial_product.
	De même que Option, Portfolio et les autres classes héritées de Financial_product, Basic_product sert à construire les produits 
	financiers; contrairement à Vanilla_products qui sert à stocker toutes les données dans un data_frame.*/

class Basic_products : public Financial_product
{
public:
	Basic_products(bool x, string ul, data_frame data); // La variable booléène permet de créer le sous jacent si x est vraie, et l'actif sans risque sinon.
	Basic_products();
	~Basic_products();
};

