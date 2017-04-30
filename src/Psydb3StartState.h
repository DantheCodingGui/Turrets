#pragma once
#include "Psydb3State.h"
class Psydb3StartState :
	public Psydb3State
{
public:
	Psydb3StartState(BaseEngine* pEngine);
	~Psydb3StartState();
	virtual void SetupBackgroundBuffer();
	virtual bool ShouldAct() { return true; };
};

