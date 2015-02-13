#pragma once
#include "data_frame.h"
#include "greeks.h"

/*	Cette classe définit les produits de base : le sous jacent lui même et l'actif sans risque.
	La structure du programme est prévue pour s'adapter facilement à une modification du nombre de sous-jacents.
	Basic_products est hérité de Financial_product. */

class Basic_products : public Financial_product
{
public:
	Basic_products(bool x, string ul, const data_frame &data); 
	// La variable booléène permet de créer le sous jacent si x est vraie, et l'actif sans risque sinon.
	Basic_products();
	~Basic_products();
};

