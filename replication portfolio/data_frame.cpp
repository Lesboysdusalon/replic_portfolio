#include "data_frame.h"
#include <algorithm>
using namespace std;

// Détermine le dernier indice trouvé
// Fonctionne uniquement sur des vecteurs ayant tous leurs éléments differents
int search_st(vector<string> l, string s)  
{
	int	k = 0;
	for (int i = 0; i < l.size(); i++){
		if (l[i] == s)
		{
			k = i;
		};
	};
	return k;
}

data_frame::data_frame(vector<string> s, vector<vector<float> > v)
{
	label = s;
	data = v;
}

data_frame::data_frame()
{

}


data_frame::~data_frame()
{
}


vector<float> data_frame::getnav(string s)
{
	int k = search_st(label, s);
	vector<float> res = data[k];
	return res;
}
