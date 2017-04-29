#pragma once
#include "Psydb3State.h"
class Psydb3PlayState :
	public Psydb3State
{
public:
	Psydb3PlayState();
	~Psydb3PlayState();
	virtual void SetupBackgroundBuffer();
	virtual bool ShouldAct() { return true; };
};

