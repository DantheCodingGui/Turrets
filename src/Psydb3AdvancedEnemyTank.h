#pragma once
#include "Psydb3EnemyTank.h"
class Psydb3AdvancedEnemyTank :
	public Psydb3EnemyTank
{
public:
	Psydb3AdvancedEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name);
	~Psydb3AdvancedEnemyTank();
	virtual void InitialiseSpriteImages();
};

