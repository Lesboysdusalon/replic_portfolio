#pragma once
#include "underlyings.h"
using namespace std;

// Le code de se fichier est issu de la source suivante : http://www.cplusplus.com/forum/beginner/10756/
// Il permet d'importer des fichiers CSV.

/*	Les données concernant le cours historique des underlyings est téléchargée via
	le site Yahoofinance sous format CSV. 
	Il faut donc importer les données sous C++ sous la forme d'une matrice.*/
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

