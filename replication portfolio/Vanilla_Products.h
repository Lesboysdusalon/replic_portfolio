#pragma once
#include "Option.h"

using namespace std;

class Vanilla_Products : data_frame 
{
public:
	Vanilla_Products(string, deque<int>, deque<int>, deque<double>, deque<string>);
	Vanilla_Products();
	~Vanilla_Products();
};