#include <iostream>
#include "portfolio.h"
#include "data_frame.h"
#include "underlyings.h"
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Extraction des cours des sous-jacents téléchargés en csv
int main()
{
	data_t data;

	string filename;
	cout << "File to read> ";
	getline(cin, filename);

	data.load(filename);

	cout << "The data is:\n";
	data.save(cout);

	return 0;
}
