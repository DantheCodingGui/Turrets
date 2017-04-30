#pragma once
#include "Psydb3State.h"
#include "Psydb3TileManager.h"
#include "Psydb3FileIO.h"
#include <vector>
#include <string>
#include "Psydb3Engine.h"
using namespace std;

class Psydb3PlayState :
	public Psydb3State
{
public:
	Psydb3PlayState(Psydb3Engine* pEngine);
	~Psydb3PlayState();
	virtual void SetupBackgroundBuffer();
	virtual void Update();
	virtual void HandleKeys(int iKeyCode);
	void GetMaps();
	void NextLevel() {
		if (m_level != m_maps.size() - 1) 
			++m_level; 
	};
private:
	Psydb3TileManager m_oTiles;

	Psydb3FileIO m_fileHandler;

	vector<vector<string>> m_maps;
	const char* m_mapFilePath;

	int m_level;
};

