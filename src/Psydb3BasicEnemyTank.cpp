#include "Psydb3BasicEnemyTank.h"


Psydb3BasicEnemyTank::Psydb3BasicEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name, unsigned int colours[3])
	: Psydb3EnemyTank(pEngine, x, y, collisionHandler, bulletManager, name, colours) {
	m_direction = 0;
	InitialiseTankStates();
}


Psydb3BasicEnemyTank::~Psydb3BasicEnemyTank() {
	delete m_spriteImages[0];
}

void Psydb3BasicEnemyTank::InitialiseSpriteImages() {
	m_spriteImages[0] = new ImageData();
	m_spriteImages[0]->LoadImage("TankSprites/StaticEnemy/default.png");
}