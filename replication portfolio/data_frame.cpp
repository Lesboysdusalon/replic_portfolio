#include "data_frame.h"
using namespace std;


data_frame::data_frame(deque<string> s, deque<deque<double> > v)
{
	_label = s;
	_data = v;
}

// Cette fonction permet de convertir un vecteur de taux quaterly compounded en un vecteur de taux continuously compounded
// Cela nous perment d'utiliser la formule de Black-Scholes
// A partir de maintenant, le taux utilis� sera le taux libor continuously compounded
deque<double> converter_to_continuously_compounded_rate(deque<double> rate)
{
	deque<double> continuously_compounded_rate;
	double m = 360 / 91;
	for (size_t i = 0; i < rate.size(); i++)
	{
		continuously_compounded_rate.push_back(m*log(1 + rate[i] / m));
	}
	return continuously_compounded_rate;
}


// Ici est d�ifini le constructeur de data_frame qui nous permettra de creer la base de donn�es data.
data_frame::data_frame(deque<string> s,const string& filename)
{
	_label = s;
	data_t csv_data;  
	csv_data.load(filename);
	// Cette boucle permet de transposer la matrice des donn�es, pour avoir le premier indice qui correspond � l'indice des variables
	for (size_t i = 0; i < csv_data[0].size(); i++)
	{
		deque<double> row;
		for (size_t j = 0; j < csv_data.size(); j++)
		{
			row.push_back(csv_data[j][i]);
		}
		_data.push_back(row);
	};
	// Les lignes suivantes permettent de convertir les taux aussit�t l'importation faite
	deque<double> libor = converter_to_continuously_compounded_rate(this->getnav("LIBOR 3M USD"));
	_data[1] = libor; // RQ : toujours faire attention � placer le taux LIBOR en seconde position du fichier csv, sinon l'indice est � changer
	// Les instructions suivantes permettent d'exprimer la volatilit� comme un nombre plut�t qu'un pourcentage, ce qui n'est pas le cas initialement.
	deque<double> vol;
	for (size_t i = 0; i < _data[0].size(); i++)
	{
		vol.push_back(_data[0][i] / 100); // RQ : toujours penser � mettre la volatilit� en premier, dans le cas o� il y a plusieurs volatilit�s, il faut r�impl�menter cette fonction
	}
	_data[0] = vol;
}

data_frame::data_frame()
{

}


data_frame::~data_frame()
{
}


deque<double> data_frame::getnav(string s)  // Cette fonction tr�s utile permet de r�cup�rer une des s�ries de donn�es du data_frame � partir de son �tiquette
{
	int k = distance(_label.begin(), find(_label.begin(), _label.end(), s)); // Cela permet de r�cup�rer l'indice de la variable recherch�e
	deque<double> res = _data[k];
	return res;
}

void data_frame::include_financial_product(Financial_product a, string name)
{
	_data.push_back(a._nav);
	_data.push_back(a._delta);
	_data.push_back(a._gamma);
	_data.push_back(a._rho);
	_data.push_back(a._theta);
	_data.push_back(a._vega);
	_label.push_back(name + "_nav");
	_label.push_back(name + "_theta");
	_label.push_back(name + "_gamma");
	_label.push_back(name + "_rho");
	_label.push_back(name + "_theta");
	_label.push_back(name + "_vega");
}



