#pragma once
#include <vector>
#include <iostream>
using namespace std;

/*D�finition de la classe Data Frame, de la m�me fa�on que sur R, de mani�re � stocker les donn�es d'underlyings et autres*/

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