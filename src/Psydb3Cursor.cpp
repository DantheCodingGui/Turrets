#include "Psydb3Cursor.h"
#include "header.h"
#include "templates.h"


Psydb3Cursor::Psydb3Cursor(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
	, m_x(500)
	, m_y(500) {
	m_iCurrentScreenX = m_iPreviousScreenX = m_x;
	m_iCurrentScreenY = m_iPreviousScreenY = m_y;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = 8;
	m_iDrawHeight = 8;
	SetVisible(true);
}

Psydb3Cursor::~Psydb3Cursor() {
}

void Psydb3Cursor::BoundaryDetection() {
	int screenX = GetEngine()->GetScreenWidth();
	int screenY = GetEngine()->GetScreenHeight();
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	else if (m_iCurrentScreenX + m_iDrawWidth > screenX)
		m_iCurrentScreenX = screenX - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	else if (m_iCurrentScreenY + m_iDrawHeight > screenY)
		m_iCurrentScreenY = screenY - m_iDrawHeight;
}

void Psydb3Cursor::Draw() {
	GetEngine()->DrawScreenOval( //values changed from lab notes due to changed center location
		m_iCurrentScreenX,
		m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x000000);

		StoreLastScreenPositionForUndraw();
}

void Psydb3Cursor::DoUpdate(int iCurrentTime) {
	m_x = GetEngine()->GetCurrentMouseX();
	m_y = GetEngine()->GetCurrentMouseY();
	m_iCurrentScreenX = m_x - m_iDrawWidth / 2;
	m_iCurrentScreenY = m_y - m_iDrawHeight / 2;

	BoundaryDetection();

	RedrawObjects();
}
