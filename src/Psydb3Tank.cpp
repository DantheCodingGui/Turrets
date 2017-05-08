#include "Psydb3Tank.h"
#include "header.h"
#include "templates.h"

#include "JPGImage.h"

#include <cmath>

#include "Psydb3CollisionHandler.h"
#include "Psydb3Bullet.h"

Psydb3Tank::Psydb3Tank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name)
	: DisplayableObject(pEngine)
	, Collideable(collisionHandler)
	, m_bulletManager(bulletManager)
	, m_x(x)
	, m_y(y)
	, m_name(name)
	, m_animationCount(0)
	, m_direction(0)
	, m_animated(false)
	, m_moving(false)
	, m_firing(false)
	, m_timeTillCanFire(0)
	, m_iDrawTankBaseWidth(0)
	, m_iDrawTankBaseHeight(0)
	, m_pEngine(pEngine) {

	m_iCurrentScreenX = m_iPreviousScreenX = (int)x;
	m_iCurrentScreenY = m_iPreviousScreenY = (int)y;
	
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
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

	m_tankStates[0] = new Psydb3TankDirectionState(0, 0, tankVelocities[0][0], tankVelocities[0][1], 13, 1, 28, 17,
													28, 31, 31, 28, 20, 20, 27, 27, 0, 32);
	m_tankStates[1] = new Psydb3TankDirectionState(0, 0, tankVelocities[1][0], tankVelocities[1][1], 24, 2, 39, 18,
													16, 22, 25, 19, 56, 52, 54, 57, 32, -25);
	m_tankStates[2] = new Psydb3TankDirectionState(30, 0, tankVelocities[2][0], tankVelocities[2][1], 14, 2, 29, 18,
													0, 10, 10, 0, 39, 39, 41, 41, 49, 0);
	m_tankStates[3] = new Psydb3TankDirectionState(0, 0, tankVelocities[3][0], tankVelocities[3][1], 24, 2, 39, 18,
													52, 55, 61, 58, 57, 55, 60, 61, -32, -25);

	for (int i = 0; i < 4; ++i) {
		m_tankStates[i + 4] = new Psydb3TankDirectionState(
			m_tankStates[i]->GetTransparencyX(), m_tankStates[i]->GetTransparencyY(),
			-m_tankStates[i]->GetTankVelocityX(), -m_tankStates[i]->GetTankVelocityY(),
			m_tankStates[i]->GetTurretDrawOffsetX(), m_tankStates[i]->GetTurretDrawOffsetY(),
			m_tankStates[i]->GetTankCentreOffsetX(), m_tankStates[i]->GetTankCentreOffsetY(),
			m_tankStates[i]->GetTracksShapeOffsetX(0), m_tankStates[i]->GetTracksShapeOffsetX(1),
			m_tankStates[i]->GetTracksShapeOffsetX(2), m_tankStates[i]->GetTracksShapeOffsetX(3),
			m_tankStates[i]->GetTracksShapeOffsetY(0), m_tankStates[i]->GetTracksShapeOffsetY(1),
			m_tankStates[i]->GetTracksShapeOffsetY(2), m_tankStates[i]->GetTracksShapeOffsetY(3),
			m_tankStates[i]->GetTracksOffsetX(), m_tankStates[i]->GetTracksOffsetY());
	}
}

Psydb3Tank::~Psydb3Tank() {
	for (int i = 0; i < 8; ++i)
		delete m_tankStates[i];
}

void Psydb3Tank::Draw() { 

	if (!IsVisible())
		return;

	//undraws font
	m_pEngine->CopyBackgroundPixels(
		m_x + m_tankStates[m_direction]->GetTankCentreOffsetX() - 37, 
		m_y + m_tankStates[m_direction]->GetTankCentreOffsetY() - 60, 120, 20);

	int drawImageIndex = ((m_animated) ? (m_direction % 4) + 4 : m_direction % 4);
	
	m_iDrawTankBaseWidth = m_iDrawWidth = m_spriteImages[drawImageIndex]->GetWidth();
	m_iDrawTankBaseHeight = m_iDrawHeight = m_spriteImages[drawImageIndex]->GetHeight();

	m_iDrawWidth = m_iDrawTankBaseWidth + 40;
	m_iDrawHeight = m_iDrawTankBaseHeight + 40;
	 
	m_spriteImages[drawImageIndex]->FlexibleRenderImageWithMask(m_pEngine->GetForeground(),
		0, 0, (int)m_x, (int)m_y, 
		m_iDrawTankBaseWidth,
		m_iDrawTankBaseHeight,
		0, m_tankStates[m_direction]->GetTransparencyX(),
		m_tankStates[m_direction]->GetTransparencyY());

	int turretDrawBaseX = m_tankStates[m_direction]->GetTurretDrawOffsetX();
	int turretDrawBaseY = m_tankStates[m_direction]->GetTurretDrawOffsetY();

	//draw barrel
	bool drawBelow;
	if (GetTargetY() < m_y + m_tankStates[m_direction]->GetTankCentreOffsetY())
		drawBelow = true;
	else
		drawBelow = false;
	
	if (drawBelow)
		DrawBarrel();
#
	//draw turret 
	m_pEngine->DrawScreenOval(
		(int)m_x + turretDrawBaseX,
		(int)m_y + turretDrawBaseY + 9,
		(int)m_x + turretDrawBaseX + 31 - 1,
		(int)m_y + turretDrawBaseY + 31 - 1,
		m_tankColours[1]);
	m_pEngine->DrawScreenRectangle(
		(int)m_x + turretDrawBaseX + 1,
		(int)m_y + turretDrawBaseY + 14,
		(int)m_x + turretDrawBaseX + 30 - 1,
		(int)m_y + turretDrawBaseY + 24 - 1,
		m_tankColours[1]);
	m_pEngine->DrawScreenOval(
		(int)m_x + turretDrawBaseX,
		(int)m_y + turretDrawBaseY,
		(int)m_x + turretDrawBaseX + 31 - 1,
		(int)m_y + turretDrawBaseY + 22 - 1,
		m_tankColours[0]);
	m_pEngine->DrawHollowOval(
		(int)m_x + turretDrawBaseX,
		(int)m_y + turretDrawBaseY,
		(int)m_x + turretDrawBaseX + 31 - 1,
		(int)m_y + turretDrawBaseY + 22 - 1,
		(int)m_x + turretDrawBaseX + 3,
		(int)m_y + turretDrawBaseY + 3,
		(int)m_x + turretDrawBaseX + 28 - 1,
		(int)m_y + turretDrawBaseY + 19 - 1,
		m_tankColours[2],
		m_pEngine->GetForeground());

	if (!drawBelow)
		DrawBarrel();

	//draws tank name above image
	m_pEngine->DrawScreenString(
		m_x + m_tankStates[m_direction]->GetTankCentreOffsetX() - 32, 
		m_y + m_tankStates[m_direction]->GetTankCentreOffsetY() - 60, m_name, 0x000000, m_pEngine->GetFont("Blockletter.otf", 15));

	StoreLastScreenPositionForUndraw();
}

void Psydb3Tank::DrawBarrel() {
	double xpoints[8], ypoints[8];

	//co-ordinates of start and end vector calculations
	int targetX = GetTargetX();
	int targetY = GetTargetY();
	int centreX = m_x + m_tankStates[m_direction]->GetTankCentreOffsetX(); 
	int centreY = m_y + m_tankStates[m_direction]->GetTankCentreOffsetY();

	//angle between tank and target (in radians)
	double angle = atan2(targetY - centreY, targetX - centreX); 

	double nonNegAngle = angle + M_PI;

	//compensated for the approx 30 degree angle the camera is looking at, y values are always 2/3 the size
	double angleCompensation;
	if (fmod(nonNegAngle, M_PI) <= M_PI / 2)
		angleCompensation = (2.0 / 3.0 + (fmod(M_PI / 2 - angle + M_PI, M_PI / 2) / M_PI / 2) / 3);
	else if (fmod(nonNegAngle, M_PI) > M_PI / 2)
		angleCompensation = (2.0 / 3.0 + (fmod(angle + M_PI, M_PI / 2) / M_PI / 2) / 3);

	//unit vectors facing the target
	double unitVectorX = m_unitVectorX = cos(angle);
	double unitVectorY = m_unitVectorY = sin(angle);

	unitVectorY *= angleCompensation;

	//unit vectors perpendicular to the target
	double unitPerpenVectorX = (unitVectorY / angleCompensation);
	double unitPerpenVectorY = -(unitVectorX * angleCompensation);

	//all points defined through quantities of these two vectors

	xpoints[0] = (double)centreX + (3 * unitPerpenVectorX) + (10 * unitVectorX);
	ypoints[0] = (double)centreY + (3 * unitPerpenVectorY) + (10 * unitVectorY);
	xpoints[7] = (double)centreX - (3 * unitPerpenVectorX) + (10 * unitVectorX);
	ypoints[7] = (double)centreY - (3 * unitPerpenVectorY) + (10 * unitVectorY);

	xpoints[1] = xpoints[0] + (20 * unitVectorX);
	ypoints[1] = ypoints[0] + (20 * unitVectorY);
	xpoints[6] = xpoints[7] + (20 * unitVectorX);
	ypoints[6] = ypoints[7] + (20 * unitVectorY);

	xpoints[2] = xpoints[1] + (2 * unitPerpenVectorX);
	ypoints[2] = ypoints[1] + (2 * unitPerpenVectorY);
	xpoints[5] = xpoints[6] - (2 * unitPerpenVectorX);
	ypoints[5] = ypoints[6] - (2 * unitPerpenVectorY);

	xpoints[3] = xpoints[2] + (5 * unitVectorX);
	ypoints[3] = ypoints[2] + (5 * unitVectorY);
	xpoints[4] = xpoints[5] + (5 * unitVectorX);
	ypoints[4] = ypoints[5] + (5 * unitVectorY);

	m_pEngine->DrawPolygon(
		8,
		xpoints,
		ypoints,
		m_tankColours[2],
		m_pEngine->GetForeground());
}

void Psydb3Tank::FireBullet(double x, double y, double unitVectorX, double unitVectorY, int bulletIndex) {
	//dynamic_cast<Psydb3Bullet*>(m_pEngine->GetDisplayableObject(0))->StartMoving(x, y, unitVectorX, unitVectorY);
		dynamic_cast<Psydb3Bullet*>(m_pEngine->GetDisplayableObject(bulletIndex))->StartMoving(x, y, unitVectorX, unitVectorY);

}

void Psydb3Tank::DoUpdate(int iCurrentTime) {

	GetDirection();
	int bulletIndex;

	if (m_firing && m_timeTillCanFire == 0 && (bulletIndex = m_bulletManager->RequestToFire()) != -1) {
		FireBullet(m_x + (int)m_tankStates[m_direction]->GetTankCentreOffsetX(), m_y + (int)m_tankStates[m_direction]->GetTankCentreOffsetY(),
			m_unitVectorX, m_unitVectorY, bulletIndex);
		m_firing = false;
		m_timeTillCanFire = 200;
	}
	else if (m_timeTillCanFire > 0) {
		--m_timeTillCanFire;
		m_firing = false;
	}

	if (m_moving) {
		int oldPosX = m_x;
		int oldPosY = m_y;
		m_x += m_tankStates[m_direction]->GetTankVelocityX();
		if (m_collisionHandler->CheckBackgroundCollision(this))
			m_x = oldPosX;
		m_y += m_tankStates[m_direction]->GetTankVelocityY();
		if (m_collisionHandler->CheckBackgroundCollision(this))
			m_y = oldPosY;

		m_collisionHandler->CheckBackgroundCollision(this);

		UpdateAnimation();
	}
	else
		m_collisionHandler->CheckBackgroundCollision(this);

	m_iCurrentScreenX = (int)m_x - 20;
	m_iCurrentScreenY = (int)m_y - 20;

	RedrawObjects();
}

void Psydb3Tank::UpdateAnimation() { //switch tank images for animation

	++m_animationCount;
	int animation = m_direction % 4;
	int cycleLength;

	bool oldAnim = m_animated;

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
		if (m_animationCount > (cycleLength = 1.5*abs((int)(sqrt(2 * pow(m_tankStates[m_direction]->GetTankVelocityY() * 100, 2))))))
			m_animationCount = 0;
	}
	if (m_animationCount <= cycleLength / 2) 
		m_animated = true;
	else 
		m_animated = false;

	if (m_animated != oldAnim)
		 DrawBackgroundTracks();

}

//draws the effect of the tanks marking the background over time
void Psydb3Tank::DrawBackgroundTracks() {
	double xPoints[4];
	double yPoints[4];


	for (int i = 0; i < 4; ++i) {
		xPoints[i] = m_x + (int)m_tankStates[m_direction]->GetTracksShapeOffsetX(i);
		yPoints[i] = m_y + (int)m_tankStates[m_direction]->GetTracksShapeOffsetY(i);
	}

	m_pEngine->DrawBackgroundPolygon(
		4,
		xPoints,
		yPoints,
		0xd3aa5f);


	for (int i = 0; i < 4; ++i) {
		xPoints[i] = m_x + (int)m_tankStates[m_direction]->GetTracksShapeOffsetX(i) + (int)m_tankStates[m_direction]->GetTracksOffsetX();
		yPoints[i] = m_y + (int)m_tankStates[m_direction]->GetTracksShapeOffsetY(i) + (int)m_tankStates[m_direction]->GetTracksOffsetY();
	}

	m_pEngine->DrawBackgroundPolygon(
		4,
		xPoints,
		yPoints,
		0xd3aa5f);
}

void Psydb3Tank::BackgroundCollideBehaviour(char Direction, int tileEdge) {
	switch (Direction){
		case 0:
			m_x = tileEdge - m_iDrawTankBaseWidth;
			break;
		case 1:
			m_y = tileEdge - m_iDrawTankBaseHeight;
			break;
		case 2:
			m_x = tileEdge;
			break;
		case 3:
			m_y = tileEdge;
			break;
	}
}

//since diagonal image is larger than the others, must edit 
//player position slightly when swapping to/from it
void Psydb3Tank::ImageSizeCompensation(int oldDirection, int newDirection) {
	bool oldDirSmall = (oldDirection % 2 == 0) ? true : false;
	bool newDirSmall = (newDirection % 2 == 0) ? true : false;

	int oldPosX = m_x;
	int oldPosY = m_y;

	if (oldDirSmall && !newDirSmall) {
		m_x -= 7.5;
		m_y -= 3;
	}
	else if (!oldDirSmall && newDirSmall) {
		m_x += 7.5;
		m_y += 3;
	}
	if (m_collisionHandler->CheckBackgroundCollision(this))
		m_x = oldPosX;
	if (m_collisionHandler->CheckBackgroundCollision(this))
		m_y = oldPosY;
}