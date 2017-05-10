#include "Psydb3EnemyTank.h"


Psydb3EnemyTank::Psydb3EnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name)
	: Psydb3Tank(pEngine, x, y, collisionHandler, bulletManager, name) {
	m_fireRate = 400;
}


Psydb3EnemyTank::~Psydb3EnemyTank() {
}

void Psydb3EnemyTank::GetDirection() {
	//m_direction = 0;
	//m_moving = true;
}

void Psydb3EnemyTank::DoUpdate(int iCurrentTime) {
	//m_firing = true;
	Psydb3Tank::DoUpdate(iCurrentTime);
}