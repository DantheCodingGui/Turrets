#include "Psydb3StandardEnemyTank.h"


Psydb3StandardEnemyTank::Psydb3StandardEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name)
	: Psydb3EnemyTank(pEngine, x, y, collisionHandler, bulletManager, name) {
	InitialiseTankStates();
	m_tankColours[0] = 0xAC0014;
	m_tankColours[1] = 0x7E000F;
	m_tankColours[2] = 0X2B0005;
}


Psydb3StandardEnemyTank::~Psydb3StandardEnemyTank() {
	for (int i = 0; i < 8; ++i)
		delete m_spriteImages[i];
}

void Psydb3StandardEnemyTank::InitialiseSpriteImages() {
	m_spriteImages[0] = new ImageData();
	m_spriteImages[0]->LoadImage("TankSprites/StandardEnemy/H_1.png");
	m_spriteImages[1] = new ImageData();
	m_spriteImages[1]->LoadImage("TankSprites/StandardEnemy/DL_1.png");
	m_spriteImages[2] = new ImageData();
	m_spriteImages[2]->LoadImage("TankSprites/StandardEnemy/V_1.png");
	m_spriteImages[3] = new ImageData();
	m_spriteImages[3]->LoadImage("TankSprites/StandardEnemy/DR_1.png");
	m_spriteImages[4] = new ImageData();
	m_spriteImages[4]->LoadImage("TankSprites/StandardEnemy/H_2.png");
	m_spriteImages[5] = new ImageData();
	m_spriteImages[5]->LoadImage("TankSprites/StandardEnemy/DL_2.png");
	m_spriteImages[6] = new ImageData();
	m_spriteImages[6]->LoadImage("TankSprites/StandardEnemy/V_2.png");
	m_spriteImages[7] = new ImageData();
	m_spriteImages[7]->LoadImage("TankSprites/StandardEnemy/DR_2.png");
}
