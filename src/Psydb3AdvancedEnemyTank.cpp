#include "Psydb3AdvancedEnemyTank.h"


Psydb3AdvancedEnemyTank::Psydb3AdvancedEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name)
	: Psydb3EnemyTank(pEngine, x, y, collisionHandler, bulletManager, name) {
	InitialiseTankStates();

	m_tankColours[0] = 0x3E3E3E;
	m_tankColours[1] = 0x333232;
	m_tankColours[2] = 0X171717;
}


Psydb3AdvancedEnemyTank::~Psydb3AdvancedEnemyTank() {
	for (int i = 0; i < 8; ++i)
		delete m_spriteImages[i];
}

void Psydb3AdvancedEnemyTank::InitialiseSpriteImages() {
	m_spriteImages[0] = new ImageData();
	m_spriteImages[0]->LoadImage("TankSprites/AdvancedEnemy/H_1.png");
	m_spriteImages[1] = new ImageData();
	m_spriteImages[1]->LoadImage("TankSprites/AdvancedEnemy/DL_1.png");
	m_spriteImages[2] = new ImageData();
	m_spriteImages[2]->LoadImage("TankSprites/AdvancedEnemy/V_1.png");
	m_spriteImages[3] = new ImageData();
	m_spriteImages[3]->LoadImage("TankSprites/AdvancedEnemy/DR_1.png");
	m_spriteImages[4] = new ImageData();
	m_spriteImages[4]->LoadImage("TankSprites/AdvancedEnemy/H_2.png");
	m_spriteImages[5] = new ImageData();
	m_spriteImages[5]->LoadImage("TankSprites/AdvancedEnemy/DL_2.png");
	m_spriteImages[6] = new ImageData();
	m_spriteImages[6]->LoadImage("TankSprites/AdvancedEnemy/V_2.png");
	m_spriteImages[7] = new ImageData();
	m_spriteImages[7]->LoadImage("TankSprites/AdvancedEnemy/DR_2.png");
}