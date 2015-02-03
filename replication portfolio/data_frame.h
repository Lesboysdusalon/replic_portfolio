#pragma once
#include <deque>
#include <iostream>
#include <algorithm>
#include "underlyings.h"
using namespace std;

// D�finition de la classe Data Frame, de la m�me fa�on que sur R, 
// Cela nous sert � stocker les donn�es d'underlyings entres autres

class data_frame
{
public:
	deque < string > _label;
	deque < deque<float> > _data;
	data_frame(deque<string>,deque<deque<float> >); // Constructeur basique
	data_frame(deque<string>, string); // Ce constructeur permet de sp�cifier uniquement les labels et le chemin d'acc�s du fichier csv pour importer les donn�es via les m�thodes d�finies dans underlyings.h
	data_frame();
	~data_frame();
	deque<float> getnav(string);
};

int search_st(deque<string>, string);
extern data_frame data;  // On d�clare ici la variable globale data qui contiendra toutes les donn�es, elle sera modifi�e dans diff�rente parties du programme