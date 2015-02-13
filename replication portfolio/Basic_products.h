#pragma once
#include "data_frame.h"
#include "greeks.h"

/*	Cette classe d�fini les produits de base : le sous jacent lui m�me et l'actif sans risque.
	La structure du programme est pr�vue pour accueillir plusieurs sous-jacents.
	Ainsi, on pourrait complexifier le projet en prenant en compte plusieurs sous-jacents sans rien modifier par ailleurs.
	Basic_products est h�rit� de Financial_product.
	De m�me que Option, Portfolio et les autres classes h�rit�es de Financial_product, Basic_product sert � construire les produits 
	financiers; contrairement � Vanilla_products qui sert � stocker toutes les donn�es dans un data_frame.*/

class Basic_products : public Financial_product
{
public:
	Basic_products(bool x, string ul, data_frame data); // La variable bool��ne permet de cr�er le sous jacent si x est vraie, et l'actif sans risque sinon.
	Basic_products();
	~Basic_products();
};

