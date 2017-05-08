#pragma once
#include "Psydb3EnemyTank.h"
class Psydb3StandardEnemyTank :
	public Psydb3EnemyTank
{
public:
	Psydb3StandardEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name);
	~Psydb3StandardEnemyTank();
	virtual void InitialiseSpriteImages();
	virtual void GetDirection() {};
};

