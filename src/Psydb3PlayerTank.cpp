#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"



Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine, double x, double y,
								double maxDx, double maxDy)
	: Psydb3Tank(pEngine, x, y, maxDx, maxDy) {
	InitialiseSpriteImages();
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

void Psydb3PlayerTank::DoUpdate(int iCurrentTime) {
	bool left, right, up, down;
	left = right = up = down = false;

	if (m_pEngine->IsKeyPressed(SDLK_a)) { //acceleration/deceleration in all directions
		//if (m_dx >= -m_maxDx)
		//	m_dx -= 0.1;
		m_x -= 0.2;
		left = true;
	}
	if (m_pEngine->IsKeyPressed(SDLK_d)) {
		//if (m_dx <= m_maxDx)
		//	m_dx += 0.1;
		m_x += 0.2;
		right = true;
	}
	if (m_pEngine->IsKeyPressed(SDLK_w)) {
		//if (m_dy >= -m_maxDy)
		//	m_dy -= 0.1;
		m_y -= 0.2;
		up = true;
	}
	if (m_pEngine->IsKeyPressed(SDLK_s)) {
		//if (m_dy <= m_maxDy)
		//	m_dy += 0.1;
		m_y += 0.2;
		down = true;
	}

	++m_animationCount;
	//animate();
	m_x += m_dx;
	m_y += m_dy;

	m_iCurrentScreenX = (int)m_x;
	m_iCurrentScreenY = (int)m_y;
	printf("%d, %d\n", m_iCurrentScreenX, m_iCurrentScreenY);

	checkCorrectImage(left, right, up, down);

	RedrawObjects();
}


