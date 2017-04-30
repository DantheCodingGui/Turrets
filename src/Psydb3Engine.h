#pragma once
#include "BaseEngine.h"
#include "Psydb3TileManager.h"
#include "Psydb3State.h"
#include "Psydb3FileIO.h"

class Psydb3Engine :
	public BaseEngine {
public:
	Psydb3Engine();
	~Psydb3Engine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void GameAction();
	void SetState(Psydb3State* newState) { m_gameState = newState; };
private: 
	Psydb3TileManager m_oTiles;
	int m_noOfDisplayObjects;
	
	Psydb3State* m_gameState;

	Psydb3FileIO m_fileHandler;
};

