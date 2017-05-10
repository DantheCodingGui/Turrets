#pragma once
#include "Psydb3Engine.h"

#define START_STATE	0
#define PLAY_STATE	1
#define PAUSE_STATE	2
#define END_STATE	3

class Psydb3State
{
public:
	Psydb3State(Psydb3Engine* pEngine);
	~Psydb3State();
	virtual void DrawBackground() = 0;
	virtual void Update() = 0;
	virtual void HandleKeys(int iKeyCode) = 0;
	virtual void HandleMouse() = 0;
	virtual void DrawOntop() = 0;
	virtual void UnDrawStrings() = 0;
protected:
	Psydb3Engine* m_pEngine;
};

