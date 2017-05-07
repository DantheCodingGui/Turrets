#pragma once
#include "DisplayableObject.h"
#include "Collideable.h"
#include "JPGImage.h"
#include "Psydb3RotationPosition.h"
#include "Psydb3TankDirectionState.h"
#include "Psydb3BulletManager.h"
class Psydb3Tank :
	public DisplayableObject,
	public Collideable
{
public:
	Psydb3Tank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, Psydb3BulletManager* bulletManager, const char* name);
	~Psydb3Tank();
    void Draw(); //abstract methods
	void DrawBarrel();
	void GetBarrelCoords(double* points, int targetX, int targetY);
	void FireBullet(double x, double y, double unitVectorX, double unitVectorY, int bulletIndex);
	virtual void DoUpdate(int iCurrentTime);
	virtual void GetDirection() = 0;
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
	virtual void GetEdges(int edges[4]) {
		edges[0] = m_x;
		edges[1] = m_y + 20;
		edges[2] = m_x + m_iDrawTankBaseWidth;
		edges[3] = m_y + m_iDrawTankBaseWidth;
	};
	virtual int GetCollisionCentreX() { return (int)m_x + m_iDrawTankBaseWidth / 2; };
	virtual int GetCollisionCentreY() { return (int)m_y + 10 + m_iDrawTankBaseHeight / 2; };
	virtual void BackgroundCollideBehaviour(char Direction, int tileEdge);
	void SetCollidingX(bool isColliding) { m_collidingX = isColliding; };
	void SetCollidingY(bool isColliding) { m_collidingY = isColliding; };
	void SetFiring(bool isFiring) { m_firing = isFiring; };
protected:
	double m_x;
	double m_y;
	int m_direction;
	//int m_prevDirection; //previous direction used to fix drawing bug
	bool m_animated; //is image loaded default or animated version
	bool m_moving;
	bool m_rotating; //is the tank BASE rotating
	bool m_firing;

	int m_timeTillCanFire;

	Psydb3TankDirectionState* m_tankStates[8]; //stores data specific to the direction the tank is facing

	ImageData* m_spriteImages[8]; //single sprite image object all images loaded into

	//Psydb3RotationPosition* rotator;
	Psydb3BulletManager* m_bulletManager;

	BaseEngine* m_pEngine; //stores base engine pointer for code clarity going forward

	int m_animationCount; //used to change the sprite image upon count progress

	int m_iDrawTankBaseWidth; //second set of values needed for tank barrel undraw
	int m_iDrawTankBaseHeight;

	double m_unitVectorX;
	double m_unitVectorY;

	const char* m_name;
};

