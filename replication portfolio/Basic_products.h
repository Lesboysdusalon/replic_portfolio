#pragma once
#include "data_frame.h"
#include "greeks.h"

// Cette classe défini les produits de base : le sous jacent lui même et l'actif sans risque

class Basic_products : public Financial_product
{
public:
	Basic_products(bool x, string ul, data_frame data); // La variable booléène permet de créer le sous jacent si x est vraie, et l'actif sans risque sinon.
	Basic_products();
	~Basic_products();
};

