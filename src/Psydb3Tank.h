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
	virtual void Draw(); //abstract methods
	virtual void DoUpdate() = 0;
protected:
	double m_x;
	double m_y;
	double m_dx;
	double m_dy;
	double m_maxDx; //maximum speeds of tank
	double m_maxDy;

	ImageData m_spriteImage; //single sprite image object all images loaded into

	BaseEngine* m_pEngine; //stores base engine pointer for code clarity going forward
};

