#include "data_frame.h"
using namespace std;

// D�termine le dernier indice trouv�
// Fonctionne uniquement sur des vecteurs ayant tous leurs �l�ments differents
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


// Pour cet exemple, on importe juste les quotations mensuelles du cac 40, de Jan 2000 � Dec 2014
deque<string> s;
const string filename = "..\\vix_libor_sp.csv";
data_frame data(s,filename);