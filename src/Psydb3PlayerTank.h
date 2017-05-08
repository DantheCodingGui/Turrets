#pragma once
#include "Psydb3Tank.h"
class Psydb3PlayerTank :
	public Psydb3Tank
{
public:
	Psydb3PlayerTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name, unsigned int colours[3]);
	~Psydb3PlayerTank();
	void InitialiseSpriteImages();
	virtual void GetDirection();
	virtual void DoUpdate(int iCurrentTime);
	int GetTargetX() const { return m_pEngine->GetCurrentMouseX(); };
	int GetTargetY() const { return m_pEngine->GetCurrentMouseY(); };
};

