#pragma once
#include <vector>
#include <string>
using namespace std;
class Psydb3FileIO
{
public:
	Psydb3FileIO();
	~Psydb3FileIO();

	//template<typename T> 
	void ReadTextFile(vector<string>* dataDump, const char* fileName);
};

