#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
#include "Psydb3RotationPosition.h"
#include "Psydb3TankDirectionState.h"
class Psydb3Tank :
	public DisplayableObject
{
public:
	Psydb3Tank(BaseEngine* pEngine, double x, double y);
	~Psydb3Tank();
    void Draw(); //abstract methods
	void DrawBarrel();
	void GetBarrelCoords(double* points, int targetX, int targetY);
	virtual void DoUpdate(int iCurrentTime) = 0;
	virtual int GetTargetX() = 0;
	virtual int GetTargetY() = 0;
	virtual void InitialiseSpriteImages() = 0;
	virtual void InitialiseTankStates();
	virtual void InitialiseTankVelocities(double tankVelocities[4][2]);
	void InitialiseTransparencyPixels();

	void UpdateAnimation();
	void DrawBackgroundTracks();
	inline bool ShouldStartRotating(int currentDirection, int newDirection) {
		int backCheck = currentDirection - 2;
		if (backCheck < 0)
			backCheck = backCheck + 8;
		int forwardCheck = currentDirection + 2;
		if (forwardCheck > 7)
			forwardCheck = forwardCheck - 8;
		return (newDirection == backCheck || newDirection == forwardCheck);
	};
	void ImageSizeCompensation(int oldDirection, int newDirection);
protected:
	double m_x;
	double m_y;
	int m_direction;
	//int m_prevDirection; //previous direction used to fix drawing bug
	bool m_animated; //is image loaded default or animated version
	bool m_moving;
	bool m_rotating; //is the tank BASE rotating

	Psydb3TankDirectionState* m_tankStates[8]; //stores data specific to the direction the tank is facing

	ImageData* m_spriteImages[8]; //single sprite image object all images loaded into

	//Psydb3RotationPosition* rotator;

	BaseEngine* m_pEngine; //stores base engine pointer for code clarity going forward

	int m_animationCount; //used to change the sprite image upon count progress

	int m_iDrawTankBaseWidth; //second set of values needed for tank barrel undraw
	int m_iDrawTankBaseHeight;
};

