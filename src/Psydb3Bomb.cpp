#include "Psydb3Bomb.h"


Psydb3Bomb::Psydb3Bomb(BaseEngine* pEngine, int timeCreated, int x, int y)
	: DisplayableObject(pEngine) 
	, m_explosionRadius(100)
	, m_explodeTime(timeCreated + 5000)
	, m_isRed(false)
	, m_destroyed(false){

	m_iCurrentScreenX = m_iPreviousScreenX = x;
	m_iCurrentScreenY = m_iPreviousScreenY = y;

	m_iDrawWidth = 27;
	m_iDrawHeight = 20;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	SetVisible(true);
}


Psydb3Bomb::~Psydb3Bomb() {
}

void Psydb3Bomb::Explode() {
	//actual effects here
	m_destroyed = true;
}

void Psydb3Bomb::Draw() {
	if (!m_destroyed) {
		unsigned int bombColour;
		if (m_isRed)
			bombColour = 0xff0000;
		else
			bombColour = 0xffff00;

		GetEngine()->DrawOval(
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1,
			0x777777);
		GetEngine()->DrawOval(
			m_iCurrentScreenX,
			m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1,
			m_iCurrentScreenY + m_iDrawHeight - 1 - 2,
			0xAAAAAA);
		GetEngine()->DrawOval(
			m_iCurrentScreenX + 6,
			m_iCurrentScreenY + 6,
			m_iCurrentScreenX + m_iDrawWidth - 1 - 6,
			m_iCurrentScreenY + m_iDrawHeight - 1 - 8,
			0x777777);
		GetEngine()->DrawOval(
			m_iCurrentScreenX + 6,
			m_iCurrentScreenY,
			m_iCurrentScreenX + m_iDrawWidth - 1 - 6,
			m_iCurrentScreenY + m_iDrawHeight - 1 - 10,
			bombColour);
	}
	StoreLastScreenPositionForUndraw();
}

void Psydb3Bomb::DoUpdate(int iCurrentTime) {

	if (iCurrentTime >= m_explodeTime)
		Explode();
	else if (m_explodeTime - iCurrentTime < 2000) {
		static int swapColourCountdown = 50;
		--swapColourCountdown;
		if (swapColourCountdown == 0) {
			swapColourCountdown = 50;
			m_isRed = !m_isRed;
		}
	}

	RedrawObjects();
}