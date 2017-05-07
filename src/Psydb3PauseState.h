#pragma once
#include "Psydb3State.h"
class Psydb3PauseState :
	public Psydb3State
{
public:
	Psydb3PauseState(Psydb3Engine* pEngine);
	~Psydb3PauseState();
	virtual void Update();
	virtual void DrawBackground();
	virtual void HandleKeys(int iKeyCode);
	virtual void HandleMouse();
	virtual void DrawOntop();
};

