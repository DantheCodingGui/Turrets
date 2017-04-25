#include "Psydb3TankDirectionState.h"
#include "header.h"
#include "templates.h"

Psydb3TankDirectionState::Psydb3TankDirectionState(int transparentPixelX, int transparentPixelY,
													double tankVelX, double tankVelY,
													int turretDrawOffsetX, int turretDrawOffsetY) 
	: m_transparencyPixelX(transparentPixelX)
	, m_transparencyPixelY(transparentPixelY)
	, m_tankVelocityX(tankVelX)
	, m_tankVelocityY(tankVelY)
	, m_turretDrawOffsetX(turretDrawOffsetX)
	, m_turretDrawOffsetY(turretDrawOffsetY) {
}

Psydb3TankDirectionState::~Psydb3TankDirectionState() {
}
