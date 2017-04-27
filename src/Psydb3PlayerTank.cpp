#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"

Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine, double x, double y,
								double maxDx, double maxDy)
	: Psydb3Tank(pEngine, x, y, maxDx, maxDy) {
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
	if (tempDirection != previousDirection)
		ImageSizeCompensation(previousDirection, tempDirection);
	m_direction = tempDirection;
}

void Psydb3PlayerTank::DrawBarrel() {
	double points[16];
	double xpoints[8], ypoints[8];

	GetBarrelCoords(points);

	for (int i = 0; i < 8; ++i) {
		xpoints[i] = points[i];
		ypoints[i] = points[i + 8];
		//printf("x: %f, y: %f\n", xpoints[i], ypoints[i]);
	}

	m_pEngine->DrawPolygon(
		8, 
		xpoints,//XARRAY
		ypoints,//YARRAY
		0X0b290a,
		m_pEngine->GetForeground());

}

void Psydb3PlayerTank::GetBarrelCoords(double points[]) {
	int centreX = m_x + m_tankStates[m_direction]->GetTankCentreOffsetX();
	int centreY = m_y + m_tankStates[m_direction]->GetTankCentreOffsetY();

	double angle = atan2(m_pEngine->GetCurrentMouseY() - centreY, m_pEngine->GetCurrentMouseX() - centreX); //in degrees
	printf("angle: %f\n", angle);
	
	double vectorX = cos(angle);
	double vectorY = sin(angle);

	double angleCompensation;

	double newAngle = angle + M_PI;
	if (fmod(newAngle, M_PI) <= M_PI/2) {
		angleCompensation = (2.0 / 3.0 + (fmod(M_PI / 2 - angle + M_PI, M_PI / 2) / M_PI / 2) / 3);
		printf("under\n");
	}
	else if (fmod(newAngle, M_PI) > M_PI / 2) {
		angleCompensation = (2.0 / 3.0 + (fmod(angle + M_PI, M_PI / 2) / M_PI / 2) / 3);
		printf("over\n");
	}

	
	vectorY *= angleCompensation;

	//printf("vecX: %f, vecY: %f\n", vectorX, vectorY);

	int mouseX = m_pEngine->GetCurrentMouseX();
	int mouseY = m_pEngine->GetCurrentMouseY();

	double perpendicularVectorX = (vectorY / angleCompensation);
	double perpendicularVectorY = -(vectorX * angleCompensation);

	double xPerpendicular = 3 * perpendicularVectorX;
	double yPerpendicular = 3 * perpendicularVectorY;

	double xThinBarrel = 20 * vectorX;
	double yThinBarrel = 20 * vectorY;

	points[0] = centreX + xPerpendicular + xThinBarrel / 2 + 2;
	points[8] = centreY + yPerpendicular + yThinBarrel / 2 + 2;
	points[7] = centreX - xPerpendicular + xThinBarrel / 2 + 2;
	points[15] = centreY - yPerpendicular + yThinBarrel / 2 + 2;

	points[1] = points[0] + xThinBarrel;
	points[9] = points[8] + yThinBarrel;
	points[6] = points[7] + xThinBarrel;
	points[14] = points[15] + yThinBarrel;

	points[2] = points[1] + xPerpendicular / 3;
	points[10] = points[9] + yPerpendicular / 3;
	points[5] = points[6] - xPerpendicular / 3;
	points[13] = points[14] - yPerpendicular / 3;

	double xThickBarrel = 5 * vectorX;
	double yThickBarrel = 5 * vectorY;

	points[3] = points[2] + xThickBarrel;
	points[11] = points[10] + yThickBarrel;
	points[4] = points[5] + xThickBarrel;
	points[12] = points[13] + yThickBarrel;
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
		m_x += m_tankStates[m_direction]->GetTankVelocityX();
		m_y += m_tankStates[m_direction]->GetTankVelocityY();

		UpdateAnimation();
	}
	else
		m_animationCount = 0;

	//m_x += m_dx;
	//m_y += m_dy;

	m_iCurrentScreenX = (int)m_x;
	m_iCurrentScreenY = (int)m_y;

	RedrawObjects();
}