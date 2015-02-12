#pragma once
#include "reg_matrix.h"
#include <dataanalysis.h>
using namespace std;

// test de la régresion linéraire avec un portefeuille composé d'une option ayant ces caractéristiques :
// ul = "sp", ie S&P500
// maturity = 300
// strike = 1200
// order = 0, ie l'option est crée à t=0
// type = "call"


void main()
{
	// Création du data_frame contenant des données importées

	// Ici est spécifié les labels des données à importer, ainsi que la localisation du fichier csv
	deque<string> s = { "vol_sp", "LIBOR 3M USD", "sp" };
	const string filename = "..\\vix_libor_sp.csv";
	
	// Et voilà la création du data frame
	data_frame data(s, filename); // On limite la régression avant que l'option n'arrive à maturité

	// Création de l'option
	Option opt("sp", 300, 0, 1200, "call", data);
	
	// Création du Portfolio constitué de cette option
	Portfolio port(opt._nav, "sp", data);
	
	// Création de la base de produits vanilles
	deque<int> maturity = { 100, 150, 200, 300, 500 };
	deque<int> order = { 0, 50 }; // ATTENTION : par souci de cohérence, order est nécessairement toujours inférieur à maturity
	deque<double> strike = { 800, 1000, 1200, 1500 };
	deque<string> type = { "call", "put" };
	Vanilla_Products van("sp", maturity, order, strike, type, data);

	// Création de la matrice de régression

	int begin = 0;
	int end = 300;
	reg_matrix m(port, van, begin, end);

	// On enregistre les labels pour l'interprétation des résultats
	deque<string> label = m._label;

	// Convertion de la matrice en real_2d_array
	alglib::real_2d_array mat = convert_matrix(m._data);
	int nb_obs = m._data[0].size();
	int nb_vars = m._data.size();

	// Regression linéaire
	alglib::linearmodel result;
	alglib::ae_int_t info;
	alglib::lrreport ar;
	alglib::lrbuild(mat, nb_obs, nb_vars, info, result, ar);
	cout << "hello";
}


