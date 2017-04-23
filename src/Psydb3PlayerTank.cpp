#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"



Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine, double x, double y,
								double maxDx, double maxDy)
	: Psydb3Tank(pEngine, x, y, maxDx, maxDy) {
	InitialiseSpriteImages();
	InitialiseTankVelocities();
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
	else
		m_moving = false;
}

void Psydb3PlayerTank::DoUpdate(int iCurrentTime) {
	
	GetDirection();

	if (m_moving) {
#if 0
		switch (m_direction) {
			case (0) :
				m_x -= 0.4;
				break;
			case (1) :
				m_x -= 0.3;
				m_y -= 0.2;
				break;
			case (2) :
				m_y -= 0.4;
				break;
			case (3) :
				m_x += 0.3;
				m_y -= 0.2;
				break;
			case (4) :
				m_x += 0.4;
				break;
			case (5) :
				m_x += 0.3;
				m_y += 0.2;
				break;
			case (6) :
				m_y += 0.4;
				break;
			case (7) :
				m_x -= 0.3;
				m_y += 0.2;
				break;
		}
#endif
		m_x += m_tankVelocities[m_direction][0];
		m_y += m_tankVelocities[m_direction][1];
#if 0
		if (m_direction == 4) {
			++m_animationCount;
			if (m_animationCount > 40)
				m_animationCount = 0;
			if (m_animationCount <= 20)
				m_animated = true;
			else
				m_animated = false;
		}
#endif
		UpdateAnimation();
	}
	else
		m_animationCount = 0;

	//UpdateAnimation();
	//m_x += m_dx;
	//m_y += m_dy;

	m_iCurrentScreenX = (int)m_x;
	m_iCurrentScreenY = (int)m_y;
	printf("%d, %d\n", m_iCurrentScreenX, m_iCurrentScreenY);

	RedrawObjects();
}


