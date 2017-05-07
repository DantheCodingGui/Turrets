#pragma once

class Psydb3CollisionHandler;

class Collideable
{
public:
	Collideable(Psydb3CollisionHandler* collisionHandler);
	~Collideable();
	virtual int GetCollisionCentreX() = 0;
	virtual int GetCollisionCentreY() = 0;
	virtual void GetEdges(int edges[4]) = 0;
	virtual void BackgroundCollideBehaviour(char Direction, int tileEdge) = 0;
	void SetCollidingX(bool isColliding) { m_collidingX = isColliding; };
	void SetCollidingY(bool isColliding) { m_collidingY = isColliding; };
	void SetBehindTile(bool isBehindTile) { m_behindTile = isBehindTile; };
protected:
	Psydb3CollisionHandler* m_collisionHandler;

	bool m_collidingX;
	bool m_collidingY;

	bool m_behindTile;
};

