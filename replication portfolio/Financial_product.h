#pragma once
#include <deque>
using namespace std;

/*	La classe Financial_product permet de donner une structure commune aux différents produits financiers que l'on manipule
	Les différents produits construits à partir de cette classe seront : Portfolio, Options, et les basic_products : le risk free asset 
	et le sous jacent.*/

class Financial_product
{
public:
	deque<double> _nav;
	string _ul;
	deque<double> _delta;
	deque<double> _gamma;
	deque<double> _vega;
	deque<double> _rho;
	deque<double> _theta;
	Financial_product();
	~Financial_product();
};
