#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// cr�ation de la structure data_t, elle va permettre de stocker les donn�es
// deque est plus adapt� que deque en raison de la taille de la base de donn�es

struct data_t : deque <deque <float> >
{
	typedef deque <deque <float> > ::iterator record_iterator;
	typedef deque        <float>   ::iterator field_iterator;
	bool load(const string&);
	bool save(const string&);
	bool save(ostream&);
	void import_data();
};

