#pragma once
#include <vector>
#include <iostream>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// cr�ation de la structure data_t
// deque est plus adapt� que vector en raison de la taille de la base de donn�es

struct data_t : deque <deque <float> >
{
	typedef deque <deque <float> > ::iterator record_iterator;
	typedef deque        <float>   ::iterator field_iterator;
	bool load(const string& filename);
	bool save(const string& filename);
	bool save(ostream& outs);
};

