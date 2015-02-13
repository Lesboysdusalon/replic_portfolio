#pragma once
#include "reg_matrix.h"
#include <dataanalysis.h>
using namespace std;

/*	Test de la régresion linéraire avec un portefeuille composé d'une option ayant ces caractéristiques :
	ul = "sp", ie S&P500
	maturity = 300
	strike = 1200
	order = 0, ie l'option est crée à t=0
	type = "call". */

int main()
{
	// Création du data_frame contenant des données importées

	// Ici sont spécifiés les labels des données à importer, ainsi que la localisation du fichier csv
	deque<string> s = { "vol_sp", "LIBOR 3M USD", "sp" };
	const string filename = "..\\vix_libor_sp.csv";
	
	// Et voilà la création du data_frame
	data_frame data(s, filename); 

	// Création de l'option
	Option opt("sp", 300, 0, 1200.0, "call", data);
	
	// Création du Portfolio constitué de cette option
	Portfolio port(opt._nav, "sp", data);
	
	// Création de la base de produits vanilles
	deque<int> maturity = { 300 };
	deque<int> order = { 0 }; // ATTENTION : par souci de cohérence, order est nécessairement toujours inférieur à maturity
	deque<double> strike = { 1200.0 };
	deque<string> type = { "call","put" };
	Vanilla_Products van("sp", maturity, order, strike, type, data);

	// Création de la matrice de régression

	// On limite la régression avant que l'option n'arrive à maturité
	int begin = 0;
	int end = 300;
	reg_matrix m(port, van, begin, end);

	// On enregistre les labels pour l'interprétation des résultats
	deque<string> label = m._label;


	// Convertion de la matrice en real_2d_array
	alglib::real_2d_array mat = convert_matrix(m._data);

	// Définition du nb d'observations et de variables pour la régression
	alglib::ae_int_t nb_obs = mat.rows();
	alglib::ae_int_t nb_vars = mat.cols() - 1;

	// Regression linéaire

	alglib::linearmodel result;
	alglib::ae_int_t info;
	alglib::lrreport ar;
	// RQ : le programme génère une exception à la ligne de code suivante,
	// pourtant nous avons étudié en précision le fonctionnement de la librairie et nous n'avons pas compris l'origine de l'erreur
	// La matrice de régression semble conforme à la structure demandée en argument.
	// Nous pensons que le problème vient du fait que l'importation et l'intégration de la librairie ont été mal effectuées,
	// pourtant il n'y a aucune erreur de compilation.
	// Nous avons donc essayé de réintégrer la librairie d'une nouvelle manière sans succès.
	// L'exception générée n'est pas gérée par la librairie, et il n'y a aucun message d'erreur explicite.
	alglib::lrbuild(mat, nb_obs, nb_vars, info, result, ar);
	
	// Impression des résultats
	alglib::real_1d_array coef;
	alglib::lrunpack(result, coef, nb_vars);
	for (alglib::ae_int_t i = 0; i < coef.length(); i++)
	{
		cout << label[i]+ " : " << coef[i] << endl;
	}
	cout << endl;
	return 0;
}


