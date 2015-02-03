#include "data_frame.h"
using namespace std;

// Détermine le dernier indice trouvé
// Fonctionne uniquement sur des vecteurs ayant tous leurs éléments differents
int search_st(deque<string> l, string s)  
{
	int	k = 0;
	for (int i = 0; i != l.size(); i++){
		if (l[i] == s)
		{
			k = i;
		};
	};
	return k;
}

data_frame::data_frame(deque<string> s, deque<deque<float> > v)
{
	_label = s;
	_data = v;
}

data_frame::data_frame(deque<string> s,const string& filename)
{
	_label = s;
	data_t csv_data;  
	csv_data.load(filename);
	_data = csv_data;
}

data_frame::data_frame()
{

}


data_frame::~data_frame()
{
}


deque<float> data_frame::getnav(string s)
{
	int k = search_st(_label, s);
	deque<float> res = _data[k];
	return res;
}


// Ici est spécifié les labels des données à importer, ainsi que la localisation du fichier csv
deque<string> s = { "vol_sp","LIBOR 3M USD","sp"};
const string filename = "..\\vix_libor_sp.csv";
data_frame data(s,filename);