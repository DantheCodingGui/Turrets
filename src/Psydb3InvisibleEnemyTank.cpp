#include "Psydb3InvisibleEnemyTank.h"


Psydb3InvisibleEnemyTank::Psydb3InvisibleEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, 
												Psydb3BulletManager* bulletManager, const char* name, Psydb3TileManager* map)
	: Psydb3EnemyTank(pEngine, x, y, collisionHandler, bulletManager, name, map) {
	InitialiseTankStates();
	m_iDrawWidth = m_iDrawHeight = 100;
	m_iDrawTankBaseWidth = m_iDrawTankBaseHeight = 60;
}


Psydb3InvisibleEnemyTank::~Psydb3InvisibleEnemyTank() {
}

void Psydb3InvisibleEnemyTank::Draw() {

	if (!IsVisible() || !m_alive)
		return;

	int targetX = GetTargetX();
	int targetY = GetTargetY();
	int centreX = m_x + m_tankStates[m_direction]->GetTankCentreOffsetX();
	int centreY = m_y + m_tankStates[m_direction]->GetTankCentreOffsetY();
	double angle = atan2(targetY - centreY, targetX - centreX);
	m_unitVectorX = cos(angle);
	m_unitVectorY = sin(angle);

	m_pEngine->DrawScreenString(
		m_x + m_tankStates[m_direction]->GetTankCentreOffsetX() - 32,
		m_y + m_tankStates[m_direction]->GetTankCentreOffsetY() - 60, m_name, 0x000000, m_pEngine->GetFont("Blockletter.otf", 15));

	StoreLastScreenPositionForUndraw();
}