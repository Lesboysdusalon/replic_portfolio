#pragma once
#include "underlyings.h"
#include "data_frame.h"
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*	Les donn�es concernant le cours historique des underlyings est t�l�charg�e via
	le site Yahoofinance sous format CSV. 
	Il faut donc importer les donn�es sous C++ sous la forme d'une matrice.*/
// -------------------------------------------------------------------------------

// conversion du format csv en matrice
bool data_t::load(const string& filename)
{
	string s;
	ifstream f(filename.c_str());
	while (getline(f, s))
	{
		deque <float> record;
		istringstream iss(s);
		while (getline(iss, s, ','))
		{
			float fieldvalue = 0.0f;
			istringstream(s) >> fieldvalue;
			record.push_back(fieldvalue);
		}
		this->push_back(record);
	}
	return f.good();
}

bool data_t::save(const string& filename)
{
	ofstream f(filename.c_str());
	if (!f) return false;

	return save(f);
}

bool data_t::save(ostream& outs)
{
	for (data_t::record_iterator ri = this->begin(); ri != this->end(); ri++)
	{
		for (data_t::field_iterator fi = ri->begin(); fi != ri->end(); fi++)
			outs << ((fi == ri->begin()) ? "" : ", ") << *fi;
		outs << endl;
	}
	return outs.good();
}
// On ouvre la console et ex�cute la conversion des donn�es pr�alablement t�l�charg�es
// Pour cette importation, nous nous sommes aid�s du code suivant : 
// http://www.cplusplus.com/forum/beginner/10756/