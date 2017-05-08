#include "Psydb3Bullet.h"

#include "Psydb3CollisionHandler.h"

Psydb3Bullet::Psydb3Bullet(BaseEngine* pEngine, Psydb3CollisionHandler* collisionHandler)
	: DisplayableObject(pEngine)
	, Collideable(collisionHandler)
	, m_x(0)
	, m_y(0)
	, m_dx(0)
	, m_dy(0)
	, m_hasBeenFired(false)
	, m_bouncesLeft(2)
	, m_timeTillCollisionChecking(1000)
	, m_pEngine(pEngine) {

	m_iCurrentScreenX = m_iPreviousScreenX = (int)m_x;
	m_iCurrentScreenY = m_iPreviousScreenY = (int)m_y;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = m_iDrawHeight = 15;
}


Psydb3Bullet::~Psydb3Bullet() {
}

void Psydb3Bullet::StartMoving(double x, double y, double vectorX, double vectorY) {
	if (m_hasBeenFired)
		return;
	m_x = m_iCurrentScreenX = (x - m_iDrawWidth/2) + (vectorX * 50);
	m_y = m_iCurrentScreenY = (y - m_iDrawHeight/2) + (vectorY * 50);
	m_dx = vectorX * 2;
	m_dy = vectorY * 2;
	m_hasBeenFired = true;

}

void Psydb3Bullet::Reset() {
	m_hasBeenFired = false;
	m_x = 0;
	m_y = 0;
	m_dx = 0;
	m_dy = 0;
}

void Psydb3Bullet::BackgroundCollideBehaviour(char Direction, int tileEdge) {}

void Psydb3Bullet::Draw() {
	
	if (!m_hasBeenFired || !IsVisible())
		return;

	if (m_behindTile) {
		StoreLastScreenPositionForUndraw();
		return;
	}

	//printf("x: %f, drawx: %d, y: %f, drawy: %d, velX: %f, velY: %f", m_x, m_iCurrentScreenX, m_y, m_iCurrentScreenY, m_dx, m_dy);
	m_pEngine->DrawScreenOval(
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x000000);
	m_pEngine->DrawScreenOval(
		m_iCurrentScreenX + 3,
		m_iCurrentScreenY + 2,
		m_iCurrentScreenX + 6 - 1,
		m_iCurrentScreenY + 5 - 1,
		0xffffff);
		
	StoreLastScreenPositionForUndraw();
}

void Psydb3Bullet::DoUpdate(int iCurrentTime) {

	if (!m_hasBeenFired)
		return;

	m_x += m_dx;
	if (m_collisionHandler->CheckBackgroundCollision(this)) {
		--m_bouncesLeft;
		m_x -= m_dx;
		m_dx = -m_dx;
	}

	m_y += m_dy;
	if (m_collisionHandler->CheckBackgroundCollision(this)) {
		--m_bouncesLeft;
		m_y -= m_dy;
		m_dy = -m_dy;
	}

	//if (m_timeTillCollisionChecking == 0 && m_collisionHandler->CheckObjectsCollision(this)) {
	//	Reset();
	//	printf("BULLET HIT SOMETHING\n");
	//}
	//else if (m_timeTillCollisionChecking > 0)
	//	--m_timeTillCollisionChecking;

	if (m_bouncesLeft <= 0) {
		Reset();
		m_bouncesLeft = 2;
	}
	//check collideable->collideable colision here, if so make has not been fired and "delete" it
  
	m_iCurrentScreenX = (int)m_x;
	m_iCurrentScreenY = (int)m_y;

	RedrawObjects();
}