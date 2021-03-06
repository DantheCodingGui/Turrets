#include "Psydb3BasicEnemyTank.h"


Psydb3BasicEnemyTank::Psydb3BasicEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, 
										Psydb3BulletManager* bulletManager, const char* name, Psydb3TileManager* map)
	: Psydb3EnemyTank(pEngine, x, y, collisionHandler, bulletManager, name, map) {
	InitialiseTankStates();
	m_tankColours[0] = 0xB98700;
	m_tankColours[1] = 0x765601;
	m_tankColours[2] = 0X342600;
}


Psydb3BasicEnemyTank::~Psydb3BasicEnemyTank() {
	delete m_spriteImages[0];
}

void Psydb3BasicEnemyTank::InitialiseSpriteImages() {
	m_spriteImages[0] = new ImageData();
	m_spriteImages[0]->LoadImage("TankSprites/StaticEnemy/default.png");
}

void Psydb3BasicEnemyTank::DoUpdate(int iCurrentTime) {
	Psydb3EnemyTank::DoUpdate(iCurrentTime);
	m_moving = false;
}