#pragma once
class Collideable
{
public:
	Collideable();
	~Collideable();
	virtual double GetX() const = 0;
	virtual double GetY() const = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
};

