#pragma once
class Psydb3TankDirectionState
{
public:
	Psydb3TankDirectionState(int transparentPixelX, int transparentPixelY,
		double tankVelX, double tankVelY,
		int turretDrawOffsetX, int turretDrawOffsetY,
		int tankCentreOffsetX, int tankCentreOffsetY,
		int tracks1Point1X, int tracks1Point2X, int tracks1Point3X, int tracks1Point4X,
		int tracks1Point1Y, int tracks1Point2Y, int tracks1Point3Y, int tracks1Point4Y,
		int offsetX, int offsetY);
							
	~Psydb3TankDirectionState();

	int GetTransparencyX() const { return m_transparencyPixelX; };
	int GetTransparencyY() const { return m_transparencyPixelY; };

	double GetTankVelocityX() const { return m_tankVelocityX; };
	double GetTankVelocityY() const { return m_tankVelocityY; };

	int GetTurretDrawOffsetX() const { return m_turretDrawOffsetX; };
	int GetTurretDrawOffsetY() const { return m_turretDrawOffsetY; };

	int GetTankCentreOffsetX() const { return m_tankCentreOffsetX; };
	int GetTankCentreOffsetY() const { return m_tankCentreOffsetY; };

	int GetTracksShapeOffsetX(int index) const { return m_tracks1XPoints[index]; };
	int GetTracksShapeOffsetY(int index) const { return m_tracks1YPoints[index]; };

	int GetTracksOffsetX() const { return m_tracksDrawXOffset; };
	int GetTracksOffsetY() const { return m_tracksDrawYOffset; };

private:
	int m_transparencyPixelX;
	int m_transparencyPixelY;

	double m_tankVelocityX;
	double m_tankVelocityY;

	int m_turretDrawOffsetX;
	int m_turretDrawOffsetY;

	int m_tankCentreOffsetX;
	int m_tankCentreOffsetY;

	int m_tracksDrawXOffset;
	int m_tracksDrawYOffset;

	int m_tracks1XPoints[4];

	int m_tracks1YPoints[4];
};

