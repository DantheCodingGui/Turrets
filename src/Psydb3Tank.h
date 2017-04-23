#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class Psydb3Tank :
	public DisplayableObject
{
public:
	Psydb3Tank(BaseEngine* pEngine, double x, double y,
				double maxDx, double maxDy);
	~Psydb3Tank();
    void Draw(); //abstract methods
	virtual void DoUpdate(int iCurrentTime) = 0;
	virtual void InitialiseSpriteImages() = 0;
	virtual void InitialiseTankVelocities();
	void UpdateAnimation();
protected:
	double m_x;
	double m_y;
	double m_dx;
	double m_dy;
	double m_maxDx; //maximum speeds of tank
	double m_maxDy;
	int m_direction;
	//int m_prevDirection; //previous direction used to fix drawing bug
	bool m_animated; //is image loaded default or animated version
	bool m_moving;

	ImageData* m_spriteImages[8]; //single sprite image object all images loaded into

	double m_tankVelocities[8][2];

	BaseEngine* m_pEngine; //stores base engine pointer for code clarity going forward

	int m_animationCount; //used to change the sprite image upon count progress
};

