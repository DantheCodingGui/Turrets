#pragma once
#include "Psydb3Engine.h"

#define START_STATE		0
#define PLAY_STATE		1
#define PAUSE_STATE		2
#define END_WIN_STATE	3
#define END_LOSE_STATE	4

class Psydb3State
{
public:
	Psydb3State(Psydb3Engine* pEngine);
	~Psydb3State();
	virtual void DrawBackground() = 0;
	virtual void Update() = 0;
	virtual void HandleKeys(int iKeyCode) = 0;
	virtual void HandleMouse() = 0;
protected:
	Psydb3Engine* m_pEngine;
};

