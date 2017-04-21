#pragma once
#include "Psydb3Tank.h"
#include "JPGImage.h"
class Psydb3PlayerTank :
	public Psydb3Tank
{
public:
	Psydb3PlayerTank(BaseEngine* pEngine);
	~Psydb3PlayerTank();
	void Draw();
private: 
	ImageData anim1;
};

