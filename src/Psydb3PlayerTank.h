#pragma once
#include "Psydb3Tank.h"
class Psydb3PlayerTank :
	public Psydb3Tank
{
public:
	Psydb3PlayerTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name);
	~Psydb3PlayerTank();
	void InitialiseSpriteImages();
	virtual void GetDirection();
	virtual void DoUpdate(int iCurrentTime);
	int GetTargetX() { return m_pEngine->GetCurrentMouseX(); };
	int GetTargetY() { return m_pEngine->GetCurrentMouseY(); };
};

