#include "Psydb3EnemyTank.h"
#include <ctime>


Psydb3EnemyTank::Psydb3EnemyTank(BaseEngine* pEngine, double x, double y, Psydb3CollisionHandler* collisionHandler, 
								Psydb3BulletManager* bulletManager, const char* name, Psydb3TileManager* map)
	: Psydb3Tank(pEngine, x, y, collisionHandler, bulletManager, name)
	, m_map(map) {
	m_fireRate = 200;
}


Psydb3EnemyTank::~Psydb3EnemyTank() {
}

void Psydb3EnemyTank::GetDirection() {

	int targetTileX = m_map->GetTileXForPositionOnScreen(GetTargetX());
	int targetTileY = m_map->GetTileYForPositionOnScreen(GetTargetY());
	int sourceTileX = m_map->GetTileXForPositionOnScreen(m_x + m_tankStates[m_direction]->GetTankCentreOffsetX());
	int sourceTileY = m_map->GetTileYForPositionOnScreen(m_y + m_tankStates[m_direction]->GetTankCentreOffsetY());

	if (targetTileX > sourceTileX && targetTileY > sourceTileY)
		m_direction = 3;
	else if (targetTileX > sourceTileX && targetTileY < sourceTileY)
		m_direction = 5;
	else if (targetTileX < sourceTileX && targetTileY > sourceTileY)
		m_direction = 7;
	else if (targetTileX < sourceTileX && targetTileY < sourceTileY)
		m_direction = 1;
	else if (targetTileX > sourceTileX)
		m_direction = 4;
	else if (targetTileX < sourceTileX)
		m_direction = 0;
	else if (targetTileY < sourceTileY)
		m_direction = 2;
	else if (targetTileY < sourceTileY)
		m_direction = 6;
}

void Psydb3EnemyTank::DoUpdate(int iCurrentTime) {
	m_firing = true;
	m_moving = true;

	//bresenham line drawing algorithm
	//if tile line between player and enemy includes a wall, don't shoot

	int xSourceTile = m_map->GetTileXForPositionOnScreen(m_x + m_tankStates[m_direction]->GetTankCentreOffsetX());
	int ySourceTile = m_map->GetTileYForPositionOnScreen(m_y + m_tankStates[m_direction]->GetTankCentreOffsetY());

	int xTargetTile = m_map->GetTileXForPositionOnScreen(GetTargetX());
	int yTargetTile = m_map->GetTileYForPositionOnScreen(GetTargetY());

	int temp;
	bool steep = abs(yTargetTile - ySourceTile) > abs(xTargetTile - xSourceTile);
	if (steep) {
		temp = xSourceTile;
		xSourceTile = ySourceTile;
		ySourceTile = temp;

		temp = xTargetTile;
		xTargetTile = yTargetTile;
		yTargetTile = temp;
	}
	if (xSourceTile > xTargetTile) { 
		temp = xTargetTile;
		xTargetTile = xSourceTile;
		xSourceTile = temp;

		temp = yTargetTile;
		yTargetTile = ySourceTile;
		ySourceTile = temp;
	}

	int dx = xTargetTile - xSourceTile;
	int dy = abs(yTargetTile - ySourceTile);
	int error = 0;
	int yStep;
	int y = ySourceTile;

	if (ySourceTile < yTargetTile)
		yStep = 1;
	else
		yStep = -1;

	for (int x = xSourceTile; x <= xTargetTile; ++x) {
		if (steep) {
			if (m_map->GetValue(y, x) == 3) {
				m_firing = true;
				break;
			}
			else if (m_map->GetValue(y, x) != 0) {
				m_firing = false;
				break;
			}
		}
		else {

			if (m_map->GetValue(x, y) != 0) {
				m_firing = false;
				break;
			}
		}
		error += dy;
		if (2 * error >= dy) {
			y += yStep;
			error -= dx;
		}
	}
	if (m_firing)
		m_moving = false;

	Psydb3Tank::DoUpdate(iCurrentTime);
}