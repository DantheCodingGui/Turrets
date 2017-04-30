#pragma once
#include "Psydb3State.h"
class Psydb3PauseState :
	public Psydb3State
{
public:
	Psydb3PauseState(BaseEngine* pEngine);
	~Psydb3PauseState();
	virtual bool ShouldAct() { return false; };
	virtual void SetupBackgroundBuffer();
};

