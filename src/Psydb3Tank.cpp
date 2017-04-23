#include "Psydb3Tank.h"
#include "header.h"
#include "templates.h"

#include "JPGImage.h"

#include <cmath>

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

//default tank speeds (if change needed can redefine for individual tank type)
void Psydb3Tank::InitialiseTankVelocities() {
	m_tankVelocities[0][0] = -0.4;
	m_tankVelocities[0][1] = 0;

	m_tankVelocities[1][0] = -0.3;
	m_tankVelocities[1][1] = -0.2;

	m_tankVelocities[2][0] = 0;
	m_tankVelocities[2][1] = -0.4;

	m_tankVelocities[3][0] = 0.3;
	m_tankVelocities[3][1] = -0.2;

	for (int i = 4; i < 8; ++i) {
		m_tankVelocities[i][0] = -m_tankVelocities[i - 4][0];
		m_tankVelocities[i][1] = -m_tankVelocities[i - 4][1];
	}
	//for (int i = 0; i < 8; ++i) {
	//	printf("%f, %f\n", m_tankVelocities[i][0], m_tankVelocities[i][1]);
	//}
}

Psydb3Tank::~Psydb3Tank() {
}

void Psydb3Tank::Draw() { 
	int drawImageIndex = ((m_animated) ? (m_direction % 4) + 4 : m_direction % 4);
	
	m_spriteImages[drawImageIndex]->RenderImageWithMask(m_pEngine->GetForeground(),
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, 
		m_spriteImages[drawImageIndex]->GetWidth(), m_spriteImages[drawImageIndex]->GetHeight());
	//FIND A BETTER PLACE FOR THIS
	m_iDrawWidth = m_spriteImages[drawImageIndex]->GetWidth();
	m_iDrawHeight = m_spriteImages[drawImageIndex]->GetHeight();
	
	StoreLastScreenPositionForUndraw();
}

void Psydb3Tank::UpdateAnimation() { //switch tank images for animation
	++m_animationCount;
	int animation = m_direction % 4;
	int cycleLength; 
	//deciding how far tank has to move until image is swapped
	//simple for horizontal/vertical but more complex with diagonals (pythogoras used)
	if (animation == 0) {
		if (m_animationCount > (cycleLength = abs((int)(m_tankVelocities[m_direction][0] * 100))))
			m_animationCount = 0;
	}
	else if (animation == 2) {
		if (m_animationCount > (cycleLength = abs((int)(m_tankVelocities[m_direction][1] * 100))))
			m_animationCount = 0;
	}
	else if (animation == 1 || animation == 3) {
		if (m_animationCount > (cycleLength = abs((int)( sqrt(2 * pow(m_tankVelocities[m_direction][1] * 100, 2) )))))
			m_animationCount = 0;
	}
	if (m_animationCount <= cycleLength / 2)
		m_animated = true;
	else
		m_animated = false;
}