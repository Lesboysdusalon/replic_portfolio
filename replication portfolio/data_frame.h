#pragma once
#include <iostream>
#include <algorithm>
#include "underlyings.h"
#include "Financial_product.h" 
//	RQ : cette instruction a pour cons�quence une boucle d'inclusion dans les fichiers, ce qui peut menner � un probl�me 
//	au niveau de la compr�hension du code, mais cela permet de simplifier certaines fonctions.
using namespace std;

/*	D�finition de la classe Data Frame, de la m�me fa�on que sur R, 
	Cette classe nous servira � stocker les donn�es utilis�es plus tard dans la r�gression.
	Entres autres les grecques des produits financiers utilis�s pour la r�gression sur les grecques.*/


class data_frame
{
public:
	deque < string > _label;
	deque < deque<double> > _data;
	data_frame(deque<string>,deque<deque<double> >); // Constructeur basique, o� l'on d�fini les membres 
	data_frame(deque<string>,const string&); // Ce constructeur permet de sp�cifier uniquement les labels et le chemin d'acc�s du fichier csv pour importer les donn�es via les m�thodes d�finies dans underlyings.h.
	data_frame();
	~data_frame();
	void include_financial_product(const Financial_product& , string); // Cette m�thode permet de rajouter un produit financier � un data_frame
};

int search_st(deque<string>, string);
deque<double> converter_to_continuously_compounded_rate(deque<double>);
deque<double> getnav(string, const data_frame &); // Cette fonction permet d'acc�der � une des collonnes de donn�es de _data via le label correspondant