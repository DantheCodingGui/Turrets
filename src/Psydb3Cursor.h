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
private:
	int m_x;
	int m_y;
};

