#pragma once
#include "Psydb3EnemyTank.h"
class Psydb3BasicEnemyTank :
	public Psydb3EnemyTank
{
public:
	Psydb3BasicEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name, unsigned int colours[3]);
	~Psydb3BasicEnemyTank();
	virtual void InitialiseSpriteImages();
	virtual void GetDirection() {};
};

