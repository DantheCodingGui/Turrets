#include "Psydb3FileIO.h"

#include "header.h"
#include "templates.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Psydb3FileIO::Psydb3FileIO() {
}


Psydb3FileIO::~Psydb3FileIO() {
}


void Psydb3FileIO::ReadTextFile(vector<string>* dataDump, const char* fileName) {
	ifstream readFile;
	readFile.open(fileName);

	if (!readFile.is_open()) { //exception catching
		cout << "Error Opening Map Data File" << endl;
		exit(1);
	}
	string line;
	while (getline(readFile, line)) {
		dataDump->push_back(line);
		cout << line << endl;
	}
	readFile.close();
}
