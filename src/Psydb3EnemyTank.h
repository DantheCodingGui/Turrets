#pragma once
#include "Psydb3Tank.h"
#include "Psydb3PlayState.h"
class Psydb3EnemyTank :
	public Psydb3Tank
{
public:
	Psydb3EnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, 
		Psydb3BulletManager* bulletManager, const char* name, Psydb3TileManager* map);
	~Psydb3EnemyTank();
	virtual void GetDirection();
	virtual int GetTargetX() const { return dynamic_cast<Psydb3PlayState*>(dynamic_cast<Psydb3Engine*>(m_pEngine)->GetPlayState())->GetPlayerTank()->GetXCentre(); };
	virtual int GetTargetY() const { return dynamic_cast<Psydb3PlayState*>(dynamic_cast<Psydb3Engine*>(m_pEngine)->GetPlayState())->GetPlayerTank()->GetYCentre(); };
	virtual void InitialiseSpriteImages() = 0;
	virtual void DoUpdate(int iCurrentTime);
protected:
	Psydb3TileManager* m_map;

	int m_timeUntilDirectionChange;
};

