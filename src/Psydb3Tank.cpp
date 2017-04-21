#include "Psydb3Tank.h"
#include "header.h"
#include "templates.h"


Psydb3Tank::Psydb3Tank(BaseEngine* pEngine, double x, double y,
	double maxDx, double maxDy)
	: DisplayableObject(pEngine)
	, m_x(x)
	, m_y(y)
	, m_dx(0)
	, m_dy(0)
	, m_maxDx(maxDx)
	, m_maxDy(maxDy)
	, m_animationCount(0)
	, m_direction('H')
	, m_pEngine(pEngine) {

	m_iCurrentScreenX = m_iPreviousScreenX = (int)x;
	m_iCurrentScreenY = m_iPreviousScreenY = (int)y;
	

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	SetVisible(true);
}

Psydb3Tank::~Psydb3Tank()
{
}

void Psydb3Tank::Draw() { //constant draw function between all tanks

	m_spriteImage.RenderImageWithMask(m_pEngine->GetForeground(),
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, 
		m_spriteImage.GetWidth(), m_spriteImage.GetHeight());

#if 0
	GetEngine()->DrawScreenOval( //values changed from lab notes due to changed center location
		m_iCurrentScreenX + 5,
		m_iCurrentScreenY + 5,
		m_iCurrentScreenX - 5 + 50 - 1,
		m_iCurrentScreenY - 5 + 50 - 1,
		0x222222);
#endif
	StoreLastScreenPositionForUndraw();
}

void Psydb3Tank::animate() { //switch tank images for animation
	if ((m_animationCount % 150) <= 75)
		m_spriteImage.LoadImage("TankSprites/Player/H_2.png");
	else
		m_spriteImage.LoadImage("TankSprites/Player/H_1.png");
}