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
	void animate();
protected:
	double m_x;
	double m_y;
	double m_dx;
	double m_dy;
	double m_maxDx; //maximum speeds of tank
	double m_maxDy;
	char m_direction;

	ImageData m_spriteImage; //single sprite image object all images loaded into

	BaseEngine* m_pEngine; //stores base engine pointer for code clarity going forward

	int m_animationCount; //used to change the sprite image upon count progress
};

