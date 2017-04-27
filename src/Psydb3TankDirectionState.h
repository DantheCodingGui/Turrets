#pragma once
class Psydb3TankDirectionState
{
public:
	Psydb3TankDirectionState(int transparentPixelX, int transparentPixelY, 
							double tankVelX, double tankVelY, 
							int turretDrawOffsetX, int turretDrawOffsetY,
							int tankCentreOffsetX, int tankCentreOffsetY);
	~Psydb3TankDirectionState();

	int GetTransparencyX() const { return m_transparencyPixelX; };
	int GetTransparencyY() const { return m_transparencyPixelY; };

	double GetTankVelocityX() const { return m_tankVelocityX; };
	double GetTankVelocityY() const { return m_tankVelocityY; };

	int GetTurretDrawOffsetX() const { return m_turretDrawOffsetX; };
	int GetTurretDrawOffsetY() const { return m_turretDrawOffsetY; };

	int GetTankCentreOffsetX() const { return m_tankCentreOffsetX; };
	int GetTankCentreOffsetY() const { return m_tankCentreOffsetY; };
private:
	int m_transparencyPixelX;
	int m_transparencyPixelY;

	double m_tankVelocityX;
	double m_tankVelocityY;

	int m_turretDrawOffsetX;
	int m_turretDrawOffsetY;

	int m_tankCentreOffsetX;
	int m_tankCentreOffsetY;
};

