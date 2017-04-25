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

	//rotator = new Psydb3RotationPosition();

	SetVisible(true);
}

//default tank speeds (if change needed can redefine for individual tank type)
void Psydb3Tank::InitialiseTankVelocities(double tankVelocities[4][2]) {
	tankVelocities[0][0] = -0.4;
	tankVelocities[0][1] = 0;

	tankVelocities[1][0] = -0.3;
	tankVelocities[1][1] = -0.2;

	tankVelocities[2][0] = 0;
	tankVelocities[2][1] = -0.4;

	tankVelocities[3][0] = 0.3;
	tankVelocities[3][1] = -0.2;
}

void Psydb3Tank::InitialiseTankStates() {
	InitialiseSpriteImages();

	double tankVelocities[4][2];
	InitialiseTankVelocities(tankVelocities);

	m_tankStates[0] = new Psydb3TankDirectionState(0, 0, tankVelocities[0][0], tankVelocities[0][1], 13, 1);
	m_tankStates[1] = new Psydb3TankDirectionState(0, 0, tankVelocities[1][0], tankVelocities[1][1], 24, 2);
	m_tankStates[2] = new Psydb3TankDirectionState(30, 0, tankVelocities[2][0], tankVelocities[2][1], 14, 2);
	m_tankStates[3] = new Psydb3TankDirectionState(0, 0, tankVelocities[3][0], tankVelocities[3][1], 24, 2);

	for (int i = 0; i < 4; ++i) {
		m_tankStates[i + 4] = new Psydb3TankDirectionState(m_tankStates[i]->GetTransparencyX(), m_tankStates[i]->GetTransparencyY(),
			-m_tankStates[i]->GetTankVelocityX(), -m_tankStates[i]->GetTankVelocityY(),
			m_tankStates[i]->GetTurretDrawOffsetX(), m_tankStates[i]->GetTurretDrawOffsetY());
	}
}

Psydb3Tank::~Psydb3Tank() {
	//delete rotator;
	for (int i = 0; i < 8; ++i)
		delete m_tankStates[i];
}

void Psydb3Tank::Draw() { 
	int drawImageIndex = ((m_animated) ? (m_direction % 4) + 4 : m_direction % 4);
	
	//FIND A BETTER PLACE FOR THIS
	m_iDrawWidth = m_spriteImages[drawImageIndex]->GetWidth();
	m_iDrawHeight = m_spriteImages[drawImageIndex]->GetHeight();

	m_spriteImages[drawImageIndex]->FlexibleRenderImageWithMask(m_pEngine->GetForeground(),
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, 
		m_iDrawWidth, 
		m_iDrawHeight,
		0, m_tankStates[m_direction]->GetTransparencyX(),
		m_tankStates[m_direction]->GetTransparencyY());

	int turretDrawBaseX = m_tankStates[m_direction]->GetTurretDrawOffsetX();
	int turretDrawBaseY = m_tankStates[m_direction]->GetTurretDrawOffsetY();

	//draw turret 
	m_pEngine->DrawScreenOval(
		m_iCurrentScreenX + turretDrawBaseX,
		m_iCurrentScreenY + turretDrawBaseY + 9,
		m_iCurrentScreenX + turretDrawBaseX + 31 - 1,
		m_iCurrentScreenY + turretDrawBaseY + 31 - 1,
		0x144912);
	m_pEngine->DrawScreenRectangle(
		m_iCurrentScreenX + turretDrawBaseX + 1,
		m_iCurrentScreenY + turretDrawBaseY + 14,
		m_iCurrentScreenX + turretDrawBaseX + 30 - 1,
		m_iCurrentScreenY + turretDrawBaseY + 24 - 1,
		0x144912);
	m_pEngine->DrawScreenOval(
		m_iCurrentScreenX + turretDrawBaseX,
		m_iCurrentScreenY + turretDrawBaseY,
		m_iCurrentScreenX + turretDrawBaseX + 31 - 1,
		m_iCurrentScreenY + turretDrawBaseY + 22 - 1,
		0x20791E);
	m_pEngine->DrawHollowOval(
		m_iCurrentScreenX + turretDrawBaseX,
		m_iCurrentScreenY + turretDrawBaseY,
		m_iCurrentScreenX + turretDrawBaseX + 31 - 1,
		m_iCurrentScreenY + turretDrawBaseY + 22 - 1,
		m_iCurrentScreenX + turretDrawBaseX + 3,
		m_iCurrentScreenY + turretDrawBaseY + 3,
		m_iCurrentScreenX + turretDrawBaseX + 28 - 1,
		m_iCurrentScreenY + turretDrawBaseY + 19 - 1,
		0x113d0f,
		m_pEngine->GetForeground());
	
	StoreLastScreenPositionForUndraw();
}

void Psydb3Tank::UpdateAnimation() { //switch tank images for animation

	++m_animationCount;
	int animation = m_direction % 4;
	int cycleLength;

	//deciding how far tank has to move until image is swapped
	//simple for horizontal/vertical but more complex with diagonals (pythogoras used)
	if (animation == 0) {
		if (m_animationCount > (cycleLength = abs((int)(m_tankStates[m_direction]->GetTankVelocityX() * 100))))
			m_animationCount = 0;
	}
	else if (animation == 2) {
		if (m_animationCount > (cycleLength = abs((int)(m_tankStates[m_direction]->GetTankVelocityY() * 100))))
			m_animationCount = 0;
	}
	else if (animation == 1 || animation == 3) {
		if (m_animationCount > (cycleLength = abs((int)(sqrt(2 * pow(m_tankStates[m_direction]->GetTankVelocityY() * 100, 2))))))
			m_animationCount = 0;
	}
	if (m_animationCount <= cycleLength / 2)
		m_animated = true;
	else
		m_animated = false;

}

//since diagonal image is larger than the others, must edit 
//player position slightly when swapping to/from it
void Psydb3Tank::ImageSizeCompensation(int oldDirection, int newDirection) {
	bool oldDirSmall = (oldDirection % 2 == 0) ? true : false;
	bool newDirSmall = (newDirection % 2 == 0) ? true : false;
	printf("image size adjusted\n");
	if (oldDirSmall && !newDirSmall) {
		m_x -= 7.5;
		m_y -= 4;
	}
	else if (!oldDirSmall && newDirSmall) {
		m_x += 7.5;
		m_y += 4;
	}
}