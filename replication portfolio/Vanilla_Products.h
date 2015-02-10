#pragma once
#include "Option.h"

using namespace std;

class Vanilla_Products : data_frame // La classe Vanilla_product est construite à partir de la classe data_frame, on défini uniquement un constructeur supplémentaire
{
public:
	Vanilla_Products(string, deque<int>, deque<int>, deque<double>, deque<string>); 
	Vanilla_Products();
	~Vanilla_Products();
};