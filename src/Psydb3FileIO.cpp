#include "Psydb3FileIO.h"

#include "header.h"
#include "templates.h"

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Psydb3FileIO::Psydb3FileIO() {
}


Psydb3FileIO::~Psydb3FileIO() {
}

#if 0
void Psydb3FileIO::ReadFile(vector<char>* dataDump[], const char* fileName) {
	ifstream file;
	file.open(fileName);

	if (!file.is_open()) { //exception catching
		exit(EXIT_FAILURE); 
	}

	while (file.good) {

	}
}
#endif