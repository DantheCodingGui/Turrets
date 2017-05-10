#pragma once
#include "Psydb3State.h"
class Psydb3EndState :
	public Psydb3State
{
public:
	Psydb3EndState(Psydb3Engine* pEngine);
	~Psydb3EndState();
	virtual void DrawBackground() {};
	virtual void Update() {};
	virtual void HandleKeys(int iKeyCode);
	virtual void HandleMouse() {};
	virtual void DrawOntop();
	virtual void UnDrawStrings() {};
};

