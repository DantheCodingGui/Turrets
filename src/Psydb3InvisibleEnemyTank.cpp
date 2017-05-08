#include "Psydb3InvisibleEnemyTank.h"


Psydb3InvisibleEnemyTank::Psydb3InvisibleEnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name)
	: Psydb3EnemyTank(pEngine, x, y, collisionHandler, bulletManager, name) {
	InitialiseTankStates();
}


Psydb3InvisibleEnemyTank::~Psydb3InvisibleEnemyTank() {
}

void Psydb3InvisibleEnemyTank::Draw() {

	if (!IsVisible())
		return;

	m_pEngine->CopyBackgroundPixels(
		m_x + m_tankStates[m_direction]->GetTankCentreOffsetX() - 37,
		m_y + m_tankStates[m_direction]->GetTankCentreOffsetY() - 60, 120, 20);

	m_pEngine->DrawScreenString(
		m_x + m_tankStates[m_direction]->GetTankCentreOffsetX() - 32,
		m_y + m_tankStates[m_direction]->GetTankCentreOffsetY() - 60, m_name, 0x000000, m_pEngine->GetFont("Blockletter.otf", 15));

	DrawBackgroundTracks();
	StoreLastScreenPositionForUndraw();
}