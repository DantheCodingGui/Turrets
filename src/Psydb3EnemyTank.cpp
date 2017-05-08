#include "Psydb3EnemyTank.h"


Psydb3EnemyTank::Psydb3EnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name)
	: Psydb3Tank(pEngine, x, y, collisionHandler, bulletManager, name) {
}


Psydb3EnemyTank::~Psydb3EnemyTank() {
}
