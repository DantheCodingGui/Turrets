#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;
class Psydb3FileIO
{
public:
	Psydb3FileIO();
	~Psydb3FileIO();

	void ReadTextFile(vector<string>* dataDump, const char* fileName);
	void WriteTextFile();
};

