#pragma once
#include "Psydb3Tank.h"
class Psydb3PlayerTank :
	public Psydb3Tank
{
public:
	Psydb3PlayerTank(BaseEngine* pEngine, double x, double y,
					double maxDx, double maxDy);
	~Psydb3PlayerTank();
	void DrawBarrel();
	void DoUpdate(int iCurrentTime);
	void InitialiseSpriteImages();
	void GetDirection();
	void GetBarrelCoords(double points[]);
private:
	//int iTimeUntilPoll;
};

