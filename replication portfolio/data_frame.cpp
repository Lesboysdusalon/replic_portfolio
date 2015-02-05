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

data_frame::data_frame(deque<string> s, deque<deque<double> > v)
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


deque<double> data_frame::getnav(string s)
{
	int k = search_st(_label, s);
	deque<double> res = _data[k];
	return res;
}


// Ici est spécifié les labels des données à importer, ainsi que la localisation du fichier csv
deque<string> s = { "vol_sp","LIBOR 3M USD","sp"};
const string filename = "..\\vix_libor_sp.csv";
data_frame data(s,filename);

// Cette fonction permet de convertir un vecteur de taux quaterly compounded en un taux continuously compounded
// Cela nous perment d'utiliser la formule de Black-Scholes
// A partir de maintenant, le taux utilisé sera le taux libor continuously compounded
deque<double> convestion_to_continuously_compounded_rate(string interest_rate)
{
	deque<double> quaterly_compounded_rate = data.getnav(interest_rate);
	deque<double> continuously_compounded_rate;
	double m = 360 / 91;
	for (size_t i = 0; i < quaterly_compounded_rate.size(); i++)
	{
		continuously_compounded_rate[i] = m*log(1 + quaterly_compounded_rate[i] / m);
	}
	return continuously_compounded_rate;
}