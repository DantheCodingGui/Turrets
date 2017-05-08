#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"
#include "Psydb3CollisionHandler.h"

Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name)
	: Psydb3Tank(pEngine, x, y, collisionHandler, bulletManager, name) {
	InitialiseTankStates();
	m_tankColours[0] = 0x20791E;
	m_tankColours[1] = 0x144912;
	m_tankColours[2] = 0X0B290A;
}

void Psydb3PlayerTank::InitialiseSpriteImages() {
	m_spriteImages[0] = new ImageData();
	m_spriteImages[0]->LoadImage("TankSprites/Player/H_1.png");
	m_spriteImages[1] = new ImageData();
	m_spriteImages[1]->LoadImage("TankSprites/Player/DL_1.png");
	m_spriteImages[2] = new ImageData();
	m_spriteImages[2]->LoadImage("TankSprites/Player/V_1.png");
	m_spriteImages[3] = new ImageData();
	m_spriteImages[3]->LoadImage("TankSprites/Player/DR_1.png");
	m_spriteImages[4] = new ImageData();
	m_spriteImages[4]->LoadImage("TankSprites/Player/H_2.png");
	m_spriteImages[5] = new ImageData();
	m_spriteImages[5]->LoadImage("TankSprites/Player/DL_2.png");
	m_spriteImages[6] = new ImageData();
	m_spriteImages[6]->LoadImage("TankSprites/Player/V_2.png");
	m_spriteImages[7] = new ImageData();
	m_spriteImages[7]->LoadImage("TankSprites/Player/DR_2.png");
}

Psydb3PlayerTank::~Psydb3PlayerTank() {
	for (int i = 0; i < 8; ++i)
		delete m_spriteImages[i];
}

void Psydb3PlayerTank::GetDirection() {
	bool left, right, up, down;
	left = right = up = down = false;

	m_moving = true;
	int previousDirection = m_direction;

	if (m_pEngine->IsKeyPressed(SDLK_a)) 
		left = true;
	if (m_pEngine->IsKeyPressed(SDLK_d)) 
		right = true;
	if (m_pEngine->IsKeyPressed(SDLK_w)) 
		up = true;
	if (m_pEngine->IsKeyPressed(SDLK_s)) 
		down = true;

	if (left && up)
		m_direction = 1;
	else if (right && up)
		m_direction = 3;
	else if (right && down)
		m_direction = 5;
	else if (left && down)
		m_direction = 7;
	else if (left)
		m_direction = 0;
	else if (up)
		m_direction = 2;
	else if (right)
		m_direction = 4;
	else if (down)
		m_direction = 6;
	else {
		m_moving = false;
	}

	if (m_direction % 4 != previousDirection % 4) {
		ImageSizeCompensation(previousDirection, m_direction);
		m_animationCount = 0;
	}
}

void Psydb3PlayerTank::DoUpdate(int iCurrentTime) {
	Psydb3Tank::DoUpdate(iCurrentTime);

}