#pragma once
#include "DisplayableObject.h"
#include "Collideable.h"
class Psydb3Bullet :
	public DisplayableObject,
	public Collideable
{
public:
	Psydb3Bullet(BaseEngine* pEngine, Psydb3CollisionHandler* collisionHandler);
	~Psydb3Bullet();
	void Draw();
	void DoUpdate(int iCurrentTime);
	virtual void GetEdges(int edges[4]) {
		edges[0] = m_x;
		edges[1] = m_y;
		edges[2] = m_x + m_iDrawWidth;
		edges[3] = m_y + m_iDrawHeight;
	};
	virtual int GetCollisionCentreX() { return (int)m_x + m_iDrawWidth / 2; };
	virtual int GetCollisionCentreY() { return (int)m_y + 10 + m_iDrawHeight / 2; };
	virtual void BackgroundCollideBehaviour(char Direction, int tileEdge);
	void StartMoving(double x, double y, double vectorX, double vectorY);
private:
	double m_x;
	double m_y;
	double m_dx;
	double m_dy;

	BaseEngine* m_pEngine;

	bool m_hasBeenFired;

	int m_bouncesLeft;
};
