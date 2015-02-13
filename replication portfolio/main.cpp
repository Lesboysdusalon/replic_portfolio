#pragma once
#include "reg_matrix.h"
#include <dataanalysis.h>
using namespace std;

/*	Test de la r�gresion lin�raire avec un portefeuille compos� d'une option ayant ces caract�ristiques :
	ul = "sp", ie S&P500
	maturity = 300
	strike = 1200
	order = 0, ie l'option est cr�e � t=0
	type = "call". */

int main()
{
	// Cr�ation du data_frame contenant des donn�es import�es

	// Ici sont sp�cifi�s les labels des donn�es � importer, ainsi que la localisation du fichier csv
	deque<string> s = { "vol_sp", "LIBOR 3M USD", "sp" };
	const string filename = "..\\vix_libor_sp.csv";
	
	// Et voil� la cr�ation du data_frame
	data_frame data(s, filename); 

	// Cr�ation de l'option
	Option opt("sp", 300, 0, 1200.0, "call", data);
	
	// Cr�ation du Portfolio constitu� de cette option
	Portfolio port(opt._nav, "sp", data);
	
	// Cr�ation de la base de produits vanilles
	deque<int> maturity = { 300 };
	deque<int> order = { 0 }; // ATTENTION : par souci de coh�rence, order est n�cessairement toujours inf�rieur � maturity
	deque<double> strike = { 1200.0 };
	deque<string> type = { "call","put" };
	Vanilla_Products van("sp", maturity, order, strike, type, data);

	// Cr�ation de la matrice de r�gression

	// On limite la r�gression avant que l'option n'arrive � maturit�
	int begin = 0;
	int end = 300;
	reg_matrix m(port, van, begin, end);

	// On enregistre les labels pour l'interpr�tation des r�sultats
	deque<string> label = m._label;


	// Convertion de la matrice en real_2d_array
	alglib::real_2d_array mat = convert_matrix(m._data);

	// D�finition du nb d'observations et de variables pour la r�gression
	alglib::ae_int_t nb_obs = mat.rows();
	alglib::ae_int_t nb_vars = mat.cols() - 1;

	// Regression lin�aire

	alglib::linearmodel result;
	alglib::ae_int_t info;
	alglib::lrreport ar;
	// RQ : le programme g�n�re une exception � la ligne de code suivante,
	// pourtant nous avons �tudi� en pr�cision le fonctionnement de la librairie et nous n'avons pas compris l'origine de l'erreur
	// La matrice de r�gression semble conforme � la structure demand�e en argument.
	// Nous pensons que le probl�me vient du fait que l'importation et l'int�gration de la librairie ont �t� mal effectu�es,
	// pourtant il n'y a aucune erreur de compilation.
	// Nous avons donc essay� de r�int�grer la librairie d'une nouvelle mani�re sans succ�s.
	// L'exception g�n�r�e n'est pas g�r�e par la librairie, et il n'y a aucun message d'erreur explicite.
	alglib::lrbuild(mat, nb_obs, nb_vars, info, result, ar);
	
	// Impression des r�sultats
	alglib::real_1d_array coef;
	alglib::lrunpack(result, coef, nb_vars);
	for (alglib::ae_int_t i = 0; i < coef.length(); i++)
	{
		cout << label[i]+ " : " << coef[i] << endl;
	}
	cout << endl;
	return 0;
}


