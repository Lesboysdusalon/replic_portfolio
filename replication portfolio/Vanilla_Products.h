#pragma once
#include "Option.h"

using namespace std;

class Vanilla_Products : data_frame // La classe Vanilla_product est construite � partir de la classe data_frame, on d�fini uniquement un constructeur suppl�mentaire
{
public:
	Vanilla_Products(string, deque<int>, deque<int>, deque<double>, deque<string>); 
	Vanilla_Products();
	~Vanilla_Products();
};