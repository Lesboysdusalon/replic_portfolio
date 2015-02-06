#pragma once
#include "Option.h"

//docvalue
//daily_maniac993
using namespace std;

class Vanilla_Products : data_frame 
{
public:
	Vanilla_Products(string, deque<int>, deque<int>, deque<double>, deque<bool>);
	Vanilla_Products();
	~Vanilla_Products();
};