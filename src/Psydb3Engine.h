#pragma once
#include "BaseEngine.h"
#include "Psydb3TileManager.h"

class Psydb3Engine :
	public BaseEngine {
public:
	Psydb3Engine();
	~Psydb3Engine();
	void SetupBackgroundBuffer();
private: 
	Psydb3TileManager m_oTiles;
};

