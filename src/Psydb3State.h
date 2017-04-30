#pragma once
#include "BaseEngine.h"
class Psydb3State
{
public:
	Psydb3State(BaseEngine* pEngine);
	~Psydb3State();
	virtual void SetupBackgroundBuffer() = 0;
	virtual bool ShouldAct() = 0;
protected:
	BaseEngine* m_pEngine;
};

