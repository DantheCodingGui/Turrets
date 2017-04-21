#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"



Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine, double x, double y,
								double maxDx, double maxDy)
	: Psydb3Tank(pEngine, x, y, maxDx, maxDy) {
	m_spriteImage.LoadImage("TankSprites/Player/H_1.png");
	m_iDrawWidth = m_spriteImage.GetWidth();
	m_iDrawHeight = m_spriteImage.GetHeight();
}


Psydb3PlayerTank::~Psydb3PlayerTank()
{
}

void Psydb3PlayerTank::DoUpdate(int iCurrentTime) {

	if (m_pEngine->IsKeyPressed(SDLK_a)) { //acceleration/deceleration in all directions
		//if (m_dx >= -m_maxDx)
		//	m_dx -= 0.1;
		m_x -= 0.2;

	}
	if (m_pEngine->IsKeyPressed(SDLK_d)) {
		//if (m_dx <= m_maxDx)
		//	m_dx += 0.1;
		m_x += 0.2;
	}
	if (m_pEngine->IsKeyPressed(SDLK_w)) {
		//if (m_dy >= -m_maxDy)
		//	m_dy -= 0.1;
		m_y -= 0.2;
	}
	if (m_pEngine->IsKeyPressed(SDLK_s)) {
		//if (m_dy <= m_maxDy)
		//	m_dy += 0.1;
		m_y += 0.2;
	}
	++m_animationCount;
	animate();
	m_x += m_dx;
	m_y += m_dy;

	m_iCurrentScreenX = (int)m_x;
	m_iCurrentScreenY = (int)m_y;
	printf("%d, %d\n", m_iCurrentScreenX, m_iCurrentScreenY);

	RedrawObjects();
}


