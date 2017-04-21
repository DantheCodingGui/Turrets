#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"


Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine, double x, double y,
								double maxDx, double maxDy)
	: Psydb3Tank(pEngine, x, y, maxDx, maxDy) {
	m_spriteImage.LoadImage("TankSprites/Player_Tank_Horizontal_1.png");
}


Psydb3PlayerTank::~Psydb3PlayerTank()
{
}

void Psydb3PlayerTank::DoUpdate() {

	RedrawObjects();
}


