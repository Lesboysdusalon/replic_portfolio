#include "data_frame.h"
using namespace std;

/*	Ce fichier permet la création d'un data_frame.
	Le data_frame sera ensuite rempli avec les nav et grecques des Vanilla_Products et des Basic_Products.
	La base ainsi formée sera utilisés pour la régression.
	La classe data frame permet d'accéder facilement aux données via leur label. */


data_frame::data_frame(deque<string> s, deque<deque<double> > v)
{
	_label = s;
	_data = v;
}

//	Cette fonction permet de convertir un vecteur de taux quaterly compounded en un vecteur de taux continuously compounded
//	Le taux d'intérêt est également annualisé. Cela nous perment d'utiliser la formule de Black-Scholes
//	A partir de maintenant, le taux utilisé sera le taux libor continuously compounded
deque<double> converter_to_continuously_compounded_rate(deque<double> rate)
{
	deque<double> continuously_compounded_rate;
	double m = 360.0 / 91.0;
	for (size_t i = 0; i < rate.size(); i++)
	{
		continuously_compounded_rate.push_back(m*log(1 + rate[i] / (100.0*m)));
	}
	return continuously_compounded_rate;
}


//	Ici est déifini le constructeur de data_frame qui nous permettra de creer la base de données data.
data_frame::data_frame(deque<string> s,const string& filename)
{
	_label = s;
	data_t csv_data;  
	csv_data.load(filename);
	// Cette boucle permet de transposer la matrice des données, pour avoir le premier indice qui correspond à l'indice des variables
	for (size_t i = 0; i < csv_data[0].size(); i++)
	{
		deque<double> row;
		for (size_t j = 0; j < csv_data.size(); j++)
		{
			row.push_back(csv_data[j][i]);
		}
		_data.push_back(row);
	};
	// Les lignes suivantes permettent de convertir les taux aussitôt l'importation faite
	deque<double> libor = converter_to_continuously_compounded_rate(_data[1]);
	_data[1] = libor; // RQ : toujours faire attention à placer le taux LIBOR en seconde position du fichier csv, sinon l'indice est à changer
	// Les instructions suivantes permettent d'exprimer la volatilité comme un nombre plutôt qu'un pourcentage, ce qui n'est pas le cas initialement.
	deque<double> vol;
	for (size_t i = 0; i < _data[0].size(); i++)
	{
		vol.push_back(_data[0][i] / 100.0); // RQ : toujours penser à mettre la volatilité en premier, dans le cas où il y a plusieurs volatilités, il faut réimplémenter cette fonction
	}
	_data[0] = vol;
}

data_frame::data_frame()
{

}


data_frame::~data_frame()
{
}


void data_frame::include_financial_product(const Financial_product &a, string name)
{
	_data.push_back(a._nav);
	_data.push_back(a._delta);
	_data.push_back(a._gamma);
	_data.push_back(a._rho);
	_data.push_back(a._theta);
	_data.push_back(a._vega);
	_label.push_back(name + "_nav");
	_label.push_back(name + "_delta");
	_label.push_back(name + "_gamma");
	_label.push_back(name + "_rho");
	_label.push_back(name + "_theta");
	_label.push_back(name + "_vega");
}


//	Cette fonction très utile permet de récupérer une des séries de données du data_frame à partir de son étiquette
//	RQ : Cette fonction génère un Warning car elle ne renvoie pas de valeur si le label recherché n'est pas trouvé
//	Cela est normal. 
//	Si le label recherché n'est pas trouvé, le message renvoyé alerte l'utilisateur : paramètres entrés dans la fonction sont incorrects.
deque<double> getnav(string s, const data_frame &d)
{
	int k = distance(d._label.begin(), find(d._label.begin(), d._label.end(), s)); // Cela permet de récupérer l'indice de la variable recherchée
	try
	{
		if (k == d._label.size())
		{
			throw 1;
		}
		else
		{
			deque<double> res = d._data[k];
			return res;
		}
	}
	catch (int e)
	{
		cout << "getnav n'a pas trouve le label recherche" << e << endl;
	}
}

