#pragma once
#include "JPGImage.h"
class Psydb3ImageData :
	public ImageData
{
public:
	Psydb3ImageData();
	~Psydb3ImageData();
	//unsigned int GetPixel(int x, int y) const { return m_aiPixels[m_iWidth*y + x]; };
};

