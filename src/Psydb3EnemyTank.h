#pragma once
#include "Psydb3Tank.h"
class Psydb3EnemyTank :
	public Psydb3Tank
{
public:
	Psydb3EnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name);
	~Psydb3EnemyTank();
	virtual void GetDirection();
	virtual int GetTargetX() const { return dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(m_pEngine->GetArraySize() - 2))->GetXCentre(); };
	virtual int GetTargetY() const { return dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(m_pEngine->GetArraySize() - 2))->GetYCentre(); };
	virtual void InitialiseSpriteImages() = 0;
	virtual void DoUpdate(int iCurrentTime);
};

