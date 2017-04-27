#pragma once
#include "Psydb3Tank.h"
class Psydb3PlayerTank :
	public Psydb3Tank
{
public:
	Psydb3PlayerTank(BaseEngine* pEngine, double x, double y);
	~Psydb3PlayerTank();
	void DoUpdate(int iCurrentTime);
	void InitialiseSpriteImages();
	void GetDirection();
	int GetTargetX() { return m_pEngine->GetCurrentMouseX(); };
	int GetTargetY() { return m_pEngine->GetCurrentMouseY(); };
};

