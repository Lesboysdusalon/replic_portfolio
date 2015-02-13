#pragma once
#include "data_frame.h"
#include "greeks.h"

/*	Cette classe d�finit les produits de base : le sous jacent lui m�me et l'actif sans risque.
	La structure du programme est pr�vue pour s'adapter facilement � une modification du nombre de sous-jacents.
	Basic_products est h�rit� de Financial_product. */

class Basic_products : public Financial_product
{
public:
	Basic_products(bool x, string ul, const data_frame &data); 
	// La variable bool��ne permet de cr�er le sous jacent si x est vraie, et l'actif sans risque sinon.
	Basic_products();
	~Basic_products();
};

