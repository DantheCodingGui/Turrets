#pragma once
#include "BaseEngine.h"
#include "Psydb3TileManager.h"

class Psydb3State;

class Psydb3Engine :
	public BaseEngine {
public:
	Psydb3Engine();
	~Psydb3Engine();
	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void InitialiseGameStates();
	void GameAction();
	virtual void KeyUp(int iKeyCode);
	void SetState(int newStateIndex) { m_activeGameState = m_gameStates[newStateIndex]; };
private: 
	Psydb3State* m_gameStates[6];

	Psydb3State* m_activeGameState;
};

