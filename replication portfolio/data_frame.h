#pragma once
#include <iostream>
#include <algorithm>
#include "underlyings.h"
#include "Financial_product.h" 
using namespace std;

/*	Définition de la classe Data Frame, de la même façon que sur R, 
	Cette classe nous servira à stocker les données utilisées plus tard dans la régression.*/


class data_frame
{
public:
	deque < string > _label;
	deque < deque<double> > _data;
	data_frame(deque<string>,deque<deque<double> >); // Constructeur basique, où l'on défini les membres de la classe
	data_frame(deque<string>,const string&); 
	//	Ce constructeur permet de spécifier uniquement les labels et le chemin d'accès du fichier csv
	//	pour importer les données via les méthodes déclarées dans underlyings.h.
	data_frame();
	~data_frame();
	void include_financial_product(const Financial_product& , string); // Cette méthode permet de rajouter un produit financier à un data_frame
};

deque<double> converter_to_continuously_compounded_rate(deque<double>);// Cette fonction permet de convertir le taux Libor en taux continuously compounded
deque<double> getnav(string, const data_frame &); // Cette fonction permet d'accéder à une des colonnes de données de _data via le label correspondant