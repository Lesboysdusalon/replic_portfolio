#pragma once
#include "reg_matrix.h"
#include <dataanalysis.h>
using namespace std;

/* Test de la r�gresion lin�raire avec un portefeuille compos� d'une option ayant ces caract�ristiques :
ul = "sp", ie S&P500
maturity = 300
strike = 1200
order = 0, ie l'option est cr�e � t=0
type = "call" */

void main()
{
	// Cr�ation du data_frame contenant des donn�es import�es

	// Ici est sp�cifi� les labels des donn�es � importer, ainsi que la localisation du fichier csv
	deque<string> s = { "vol_sp", "LIBOR 3M USD", "sp" };
	const string filename = "..\\vix_libor_sp.csv";
	
	// Et voil� la cr�ation du data frame
	data_frame data(s, filename); // On limite la r�gression avant que l'option n'arrive � maturit�

	// Cr�ation de l'option
	Option opt("sp", 300, 0, 1200, "call", data);
	
	// Cr�ation du Portfolio constitu� de cette option
	Portfolio port(opt._nav, "sp", data);
	
	// Cr�ation de la base de produits vanilles
	deque<int> maturity = { 300 };
	deque<int> order = { 0 }; // ATTENTION : par souci de coh�rence, order est n�cessairement toujours inf�rieur � maturity
	deque<double> strike = { 1200 };
	deque<string> type = { "call","put" };
	Vanilla_Products van("sp", maturity, order, strike, type, data);

	// Cr�ation de la matrice de r�gression

	int begin = 0;
	int end = 300;
	reg_matrix m(port, van, begin, end);

	// On enregistre les labels pour l'interpr�tation des r�sultats
	deque<string> label = m._label;

	// Convertion de la matrice en real_2d_array
	alglib::real_2d_array mat = convert_matrix(m._data);
	// D�finition du nb d'observations et de variables pour la r�gression
	alglib::ae_int_t nb_obs = m._data[0].size();
	alglib::ae_int_t nb_vars = m._data.size();

	// Regression lin�aire
	alglib::linearmodel result;
	alglib::ae_int_t info;
	alglib::lrreport ar;
	alglib::lrbuild(mat, nb_obs, nb_vars, info, result, ar);
	cout << "hello";
}


