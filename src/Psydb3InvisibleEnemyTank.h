#pragma once
#include "Psydb3EnemyTank.h"
class Psydb3InvisibleEnemyTank :
	public Psydb3EnemyTank
{
public:
	Psydb3InvisibleEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name);
	~Psydb3InvisibleEnemyTank();
	virtual void InitialiseSpriteImages() {};
	virtual void GetDirection() {};
	virtual void Draw();
};

