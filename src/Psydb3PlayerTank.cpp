#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"

Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine, double x, double y)
	: Psydb3Tank(pEngine, x, y) {
	InitialiseTankStates();
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
	int tempDirection = 0;

	if (m_pEngine->IsKeyPressed(SDLK_a)) 
		left = true;
	if (m_pEngine->IsKeyPressed(SDLK_d)) 
		right = true;
	if (m_pEngine->IsKeyPressed(SDLK_w)) 
		up = true;
	if (m_pEngine->IsKeyPressed(SDLK_s)) 
		down = true;

	if (left && up)
		tempDirection = 1;
	else if (right && up)
		tempDirection = 3;
	else if (right && down)
		tempDirection = 5;
	else if (left && down)
		tempDirection = 7;
	else if (left)
		tempDirection = 0;
	else if (up)
		tempDirection = 2;
	else if (right)
		tempDirection = 4;
	else if (down)
		tempDirection = 6;
	else {
		tempDirection = m_direction;
		m_moving = false;
	}
#if 0
	if (tempDirection != previousDirection) {
		if (!ShouldStartRotating(previousDirection, tempDirection) && !m_rotating) {
			rotator->SetupRotation(m_pEngine->GetTime(), m_pEngine->GetTime() + 750, previousDirection, tempDirection);
			m_rotating = true;
		}
		else if (m_rotating) {
			m_direction = rotator->Update(m_pEngine->GetTime(), m_direction);
			if (tempDirection == m_direction) {
				rotator->Reset();
				m_rotating = false;
			}
		}
		m_animationCount = 0;
	}
#endif
	if (tempDirection % 4 != previousDirection % 4) {
		ImageSizeCompensation(previousDirection, tempDirection);
		m_animationCount = 0;
	}

	m_direction = tempDirection;
}

void Psydb3PlayerTank::DoUpdate(int iCurrentTime) {
	
	GetDirection();

	if (m_moving) {
		m_x += m_tankStates[m_direction]->GetTankVelocityX();
		m_y += m_tankStates[m_direction]->GetTankVelocityY();

		UpdateAnimation();
	}

	m_iCurrentScreenX = (int)m_x - 20;
	m_iCurrentScreenY = (int)m_y - 20;

	RedrawObjects();
}