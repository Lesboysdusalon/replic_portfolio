#pragma once
#include <iostream>
#include <algorithm>
#include "underlyings.h"
#include "Financial_product.h" 
//	RQ : cette instruction a pour conséquence une boucle d'inclusion dans les fichiers, ce qui peut menner à un problème 
//	au niveau de la compréhension du code, mais cela permet de simplifier certaines fonctions.
using namespace std;

/*	Définition de la classe Data Frame, de la même façon que sur R, 
	Cette classe nous servira à stocker les données utilisées plus tard dans la régression.
	Entres autres les grecques des produits financiers utilisés pour la régression sur les grecques.*/


class data_frame
{
public:
	deque < string > _label;
	deque < deque<double> > _data;
	data_frame(deque<string>,deque<deque<double> >); // Constructeur basique, où l'on défini les membres 
	data_frame(deque<string>,const string&); // Ce constructeur permet de spécifier uniquement les labels et le chemin d'accès du fichier csv pour importer les données via les méthodes définies dans underlyings.h.
	data_frame();
	~data_frame();
	void include_financial_product(const Financial_product& , string); // Cette méthode permet de rajouter un produit financier à un data_frame
};

int search_st(deque<string>, string);
deque<double> converter_to_continuously_compounded_rate(deque<double>);
deque<double> getnav(string, const data_frame &); // Cette fonction permet d'accéder à une des collonnes de données de _data via le label correspondant