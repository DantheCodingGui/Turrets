#pragma once
#include "Psydb3Tank.h"
class Psydb3EnemyTank :
	public Psydb3Tank
{
public:
	Psydb3EnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name);
	~Psydb3EnemyTank();
	virtual void GetDirection() = 0;
	virtual int GetTargetX() = 0;
	virtual int GetTargetY() = 0;
	virtual void InitialiseSpriteImages() = 0;
};

