#pragma once
#include <vector>
#include <iostream>
using namespace std;

// Définition de la classe Data Frame, de la même façon que sur R, 
// Cela nous sert à stocker les données d'underlyings entres autres

class data_frame
{
public:
	vector < string > label;
	vector < vector<float> > data;
	data_frame(vector<string>,vector<vector<float> >);
	data_frame();
	~data_frame();
	vector<float> getnav(string);
};

int search_st(vector<string>, string);