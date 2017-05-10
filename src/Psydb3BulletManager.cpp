#include "Psydb3BulletManager.h"
#include "Psydb3Engine.h"
#include "Psydb3Bullet.h"

#include "Psydb3PlayState.h"

Psydb3BulletManager::Psydb3BulletManager(Psydb3Engine* pEngine, int BulletNumber) 
	: m_numberOfBullets(BulletNumber)
	, m_pEngine(pEngine) {
}


Psydb3BulletManager::~Psydb3BulletManager() {
}

int Psydb3BulletManager::RequestToFire() {
	int numberOfTanks = dynamic_cast<Psydb3PlayState*>(m_pEngine->GetActiveState())->GetNumberOfTanks();
	for (int i = 0; i < m_numberOfBullets; ++i) {
		if (!dynamic_cast<Psydb3Bullet*>(m_pEngine->GetDisplayableObject(i + numberOfTanks))->GetBeenFired()) {
			return i + numberOfTanks;
		}
	}
	return -1;
}