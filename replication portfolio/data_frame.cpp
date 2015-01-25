#include "data_frame.h"
#include <algorithm>
using namespace std;

int search_st(vector<string> l, string s)  /*Donne le dernier indice trouvé, utilisé uniquement sur des vecteurs avec tout les éléments differents*/
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
