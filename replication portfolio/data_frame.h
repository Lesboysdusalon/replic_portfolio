#pragma once
#include <deque>
#include <iostream>
#include <algorithm>
#include "underlyings.h"
using namespace std;

// Définition de la classe Data Frame, de la même façon que sur R, 
// Cela nous sert à stocker les données d'underlyings entres autres

class data_frame
{
public:
	deque < string > _label;
	deque < deque<double> > _data;
	data_frame(deque<string>,deque<deque<double> >); // Constructeur basique
	data_frame(deque<string>,const string&); // Ce constructeur permet de spécifier uniquement les labels et le chemin d'accès du fichier csv pour importer les données via les méthodes définies dans underlyings.h
	data_frame();
	~data_frame();
	deque<double> getnav(string);
	void change_rate();
};

int search_st(deque<string>, string);
extern data_frame data;  // On déclare ici la variable globale data qui contiendra toutes les données
deque<double> converter_to_continuously_compounded_rate(deque<double>);