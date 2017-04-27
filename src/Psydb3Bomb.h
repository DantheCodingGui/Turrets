#pragma once
#include "DisplayableObject.h"
class Psydb3Bomb :
	public DisplayableObject
{
public:
	Psydb3Bomb(BaseEngine* pEngine, int timeCreated, int x, int y);
	~Psydb3Bomb();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void Explode();
private:
	double m_explosionRadius;
	int m_explodeTime;

	bool m_isRed;
	bool m_destroyed;
};

