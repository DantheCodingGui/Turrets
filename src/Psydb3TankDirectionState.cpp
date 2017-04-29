#include "Psydb3TankDirectionState.h"
#include "header.h"
#include "templates.h"

Psydb3TankDirectionState::Psydb3TankDirectionState(int transparentPixelX, int transparentPixelY,
													double tankVelX, double tankVelY,
													int turretDrawOffsetX, int turretDrawOffsetY,
													int tankCentreOffsetX, int tankCentreOffsetY,
													int tracks1Point1X, int tracks1Point2X, int tracks1Point3X, int tracks1Point4X,
													int tracks1Point1Y, int tracks1Point2Y, int tracks1Point3Y, int tracks1Point4Y,
													int tracksOffsetX, int tracksOffsetY)
	: m_transparencyPixelX(transparentPixelX)
	, m_transparencyPixelY(transparentPixelY)
	, m_tankVelocityX(tankVelX)
	, m_tankVelocityY(tankVelY)
	, m_turretDrawOffsetX(turretDrawOffsetX)
	, m_turretDrawOffsetY(turretDrawOffsetY)
	, m_tankCentreOffsetX(tankCentreOffsetX)
	, m_tankCentreOffsetY(tankCentreOffsetY)
	, m_tracksDrawXOffset(tracksOffsetX)
	, m_tracksDrawYOffset(tracksOffsetY) {

	m_tracks1XPoints[0] = tracks1Point1X;
	m_tracks1YPoints[0] = tracks1Point1Y;
	m_tracks1XPoints[1] = tracks1Point2X;
	m_tracks1YPoints[1] = tracks1Point2Y;
	m_tracks1XPoints[2] = tracks1Point3X;
	m_tracks1YPoints[2] = tracks1Point3Y;
	m_tracks1XPoints[3] = tracks1Point4X;
	m_tracks1YPoints[3] = tracks1Point4Y;

}

Psydb3TankDirectionState::~Psydb3TankDirectionState() {
}
