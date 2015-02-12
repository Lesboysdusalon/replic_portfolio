#pragma once
#include "data_frame.h"
#include "greeks.h"

// Cette classe d�fini les produits de base : le sous jacent lui m�me et l'actif sans risque

class Basic_products : public Financial_product
{
public:
	Basic_products(bool x, string ul, data_frame data); // La variable bool��ne permet de cr�er le sous jacent si x est vraie, et l'actif sans risque sinon.
	Basic_products();
	~Basic_products();
};

