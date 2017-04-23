#include "Psydb3Tank.h"
#include "header.h"
#include "templates.h"

#include "JPGImage.h"

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
	, m_direction(0)
	, m_animated(false)
	, m_moving(false)
	, m_pEngine(pEngine) {
	m_iCurrentScreenX = m_iPreviousScreenX = (int)x;
	m_iCurrentScreenY = m_iPreviousScreenY = (int)y;
	
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	SetVisible(true);
}

Psydb3Tank::~Psydb3Tank() {
}

void Psydb3Tank::Draw() { //constant draw function between all tanks
	int drawImageIndex = m_direction % 4;

	m_spriteImages[drawImageIndex]->RenderImageWithMask(m_pEngine->GetForeground(),
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, 
		m_spriteImages[drawImageIndex]->GetWidth(), m_spriteImages[drawImageIndex]->GetHeight());
	//FIND A BETTER PLACE FOR THIS
	m_iDrawWidth = m_spriteImages[drawImageIndex]->GetWidth();
	m_iDrawHeight = m_spriteImages[drawImageIndex]->GetHeight();
	
	StoreLastScreenPositionForUndraw();
}

void Psydb3Tank::animate() { //switch tank images for animation
	static bool animated = false;
	if (m_animationCount > 500)
		m_animationCount = 0;
	if (m_animationCount <= 250)
		if (!animated) {
			m_direction += 4;
			animated = true;
		}
	else
		if (animated) {
			m_direction -= 4;
			animated = false;
		}
}