#pragma once
#include "BaseEngine.h"
#include "Psydb3TileManager.h"
#include "Psydb3State.h"

class Psydb3Engine :
	public BaseEngine {
public:
	Psydb3Engine();
	~Psydb3Engine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void InitialiseGameStates();
	void GameAction();
	void SetState(int newStateIndex) { m_activeGameState = m_gameStates[newStateIndex]; };
private: 
	
	int m_noOfDisplayObjects;
	
	Psydb3State* m_gameStates[6];

	Psydb3State* m_activeGameState;
};

