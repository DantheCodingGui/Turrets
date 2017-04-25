#include "Psydb3Cursor.h"
#include "header.h"
#include "templates.h"


Psydb3Cursor::Psydb3Cursor(BaseEngine* pEngine)
	: DisplayableObject(pEngine)
	, m_x(500)
	, m_y(500)
	, m_width(26){
	m_iCurrentScreenX = m_iPreviousScreenX = m_x;
	m_iCurrentScreenY = m_iPreviousScreenY = m_y;

	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	m_iDrawWidth = m_iDrawHeight = m_width;

	SDL_ShowCursor(SDL_DISABLE); //disable the mouse icon while in window

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
	GetEngine()->DrawScreenOval( //middle circle
		m_iCurrentScreenX + 11,
		m_iCurrentScreenY + 11,
		m_iCurrentScreenX + m_iDrawWidth - 1 - 11,
		m_iCurrentScreenY + m_iDrawHeight - 1 - 11,
		0xE40000);

	GetEngine()->DrawScreenRectangle( //top rectangle
		m_iCurrentScreenX + 12,
		m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1 - 12,
		m_iCurrentScreenY + m_iDrawHeight - 1 - 16,
		0x000000);

	GetEngine()->DrawScreenRectangle( //bottom rectangle
		m_iCurrentScreenX + 12,
		m_iCurrentScreenY + 16,
		m_iCurrentScreenX + m_iDrawWidth - 1 - 12,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x000000);

	GetEngine()->DrawScreenRectangle( //left rectangle
		m_iCurrentScreenX,
		m_iCurrentScreenY + 12,
		m_iCurrentScreenX + m_iDrawWidth - 1 - 16,
		m_iCurrentScreenY + m_iDrawHeight - 1 - 12,
		0x000000);

	GetEngine()->DrawScreenRectangle( //right rectangle
		m_iCurrentScreenX + 16,
		m_iCurrentScreenY + 12,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1 - 12,
		0x000000);

	//FOR LOOP HERE DRAWING DOTS BETWEEN TURRET END AND CURSOR POSITION

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
