#pragma once
#include "DisplayableObject.h"
class Psydb3Cursor :
	public DisplayableObject
{
public:
	Psydb3Cursor(BaseEngine* pEngine);
	~Psydb3Cursor();
	void BoundaryDetection();
	void Draw();
	void DoUpdate(int iCurrentTime);
	int GetX() const { return m_x; };
	int GetY() const { return m_y; };
private:
	int m_x;
	int m_y;
	int m_width;
};

