#pragma once
#include <iostream>
#include <algorithm>
#include "underlyings.h"
#include "Financial_product.h" // RQ : cette instruction a pour conséquence une boucle d'inclusion dans les fichiers, ce qui peut menner à un problème au niveau de la compréhension du code, mais cela permet de simplifier certaines fonctions.
using namespace std;

// Définition de la classe Data Frame, de la même façon que sur R, 
// Cela nous sert à stocker les données d'underlyings entres autres

class data_frame
{
public:
	deque < string > _label;
	deque < deque<double> > _data;
	data_frame(deque<string>,deque<deque<double> >); // Constructeur basique, où l'on défini les membres 
	data_frame(deque<string>,const string&); // Ce constructeur permet de spécifier uniquement les labels et le chemin d'accès du fichier csv pour importer les données via les méthodes définies dans underlyings.h.
	data_frame();
	~data_frame();
	deque<double> getnav(string); // Cette méthode permet d'accéder à une des collonnes de données de _data via le label correspondant
	void include_financial_product(Financial_product, string); // Cette méthode permet de rajouter un produit financier à un data_frame
};

int search_st(deque<string>, string);
deque<double> converter_to_continuously_compounded_rate(deque<double>);