#pragma once
#include "Psydb3State.h"
class Psydb3StartState :
	public Psydb3State
{
public:
	Psydb3StartState(Psydb3Engine* pEngine);
	~Psydb3StartState();
	virtual void SetupBackgroundBuffer();
	virtual void Update();
	virtual void HandleKeys(int iKeyCode);
};

