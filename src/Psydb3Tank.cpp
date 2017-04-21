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
	, m_pEngine(pEngine) {
	m_iCurrentScreenX = x;
	m_iCurrentScreenY = y;
	//POSSIBLE REDUNDANT CODE

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
}