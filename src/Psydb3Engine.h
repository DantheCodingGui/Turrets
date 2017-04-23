#pragma once
#include "BaseEngine.h"
#include "Psydb3TileManager.h"

class Psydb3Engine :
	public BaseEngine {
public:
	Psydb3Engine();
	~Psydb3Engine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void GameAction();
private: 
	Psydb3TileManager m_oTiles;
	int m_noOfDisplayObjects;
	int m_levelNo;
};
