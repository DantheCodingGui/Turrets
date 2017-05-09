#include "Psydb3CollisionHandler.h"
#include "header.h"
#include "templates.h"
#include <vector>

#include "Psydb3Bullet.h"

#define LEFT			0
#define TOP				1
#define RIGHT			2
#define BOTTOM			3
#define LEFT_TOP		4
#define RIGHT_TOP		5
#define LEFT_BOTTOM		6
#define RIGHT_BOTTOM	7

#define FLOOR_TILE		0

Psydb3CollisionHandler::Psydb3CollisionHandler(Psydb3Engine* pEngine, Psydb3TileManager* tileManager) 
	: m_pEngine(pEngine)
	, m_map(tileManager)
	, m_foregroundEmptyColour(0xE9C977) {
#if 0
	std::vector<Collideable*> collideableObjects;
	int i;
	int endOfArray = m_pEngine->GetArraySize();
	for (i = 0; i < endOfArray; ++i) {
		Collideable* temp;
		if ((temp = dynamic_cast<Collideable*>(m_pEngine->GetDisplayableObject(i))) != NULL) {
			collideableObjects.push_back(temp);
			temp->SetCollisionHandler(this);
		}
	}

	//next divide into tanks and bullets
	endOfArray = collideableObjects.size();
	for (i = 0; i < endOfArray; ++i) {
		Psydb3Tank* temp;
		if ((temp = dynamic_cast<Psydb3Tank*>(collideableObjects[i])) != NULL)
			m_tanks.push_back(temp);
	}
	/*
	for (i = 0; i < endOfArray; ++i) {
	Psydb3Bullet* temp;
	if ((temp = dynamic_cast<Psydb3Bullet*>(collideableObjects[i])) != NULL)
	m_bullets.push_back(temp);
	}*/
#endif
}

Psydb3CollisionHandler::~Psydb3CollisionHandler() {
}

bool Psydb3CollisionHandler::CheckBackgroundCollision(Collideable* object) {

	Psydb3Bullet* bullet;

	int tileWidth = m_map->GetTileWidth();
	int tileHeight = m_map->GetTileHeight();

	int objectEdges[4];

	object->GetEdges(objectEdges);

	int adjacentTilePosLeft = objectEdges[LEFT] / tileWidth;
	int adjacentTilePosRight = objectEdges[RIGHT] / tileWidth;
	int adjacentTilePosTop = objectEdges[TOP] / tileHeight;
	int adjacentTilePosBottom = objectEdges[BOTTOM] / tileHeight;

	bool collision = false;

	for (int j = adjacentTilePosLeft; j <= adjacentTilePosRight; ++j) {
		for (int k = adjacentTilePosTop; k <= adjacentTilePosBottom; ++k) {

			int behindWall = m_map->IsTileBehindWall(j, k);
			if (behindWall == 1) {
				m_map->m_tilesToRedrawX.push_back(j);
				m_map->m_tilesToRedrawY.push_back(k + 1);
			}
			else if (behindWall == 2) {
				m_map->m_tilesToRedrawX.push_back(j);
				m_map->m_tilesToRedrawY.push_back(k + 2);
			}

			if ((bullet = dynamic_cast<Psydb3Bullet*>(object)) != NULL && m_map->IsTileBreakable(j, k)) {
				bullet->Reset();
				m_map->RemoveTile(m_pEngine, j, k);
				return true;
			}

			if (m_map->IsTileCollideable(j, k)) {
				collision = true;
			}
		}
	}
	return collision;
}

bool Psydb3CollisionHandler::PixelPerfectCollision(Collideable* object, Collideable* otherObject) {
	return true;

}

bool Psydb3CollisionHandler::CheckObjectsCollision(Collideable* object) {
	int objectEdges[4];
	int tempObjectEdges[4];
	object->GetEdges(objectEdges);

	std::vector<Collideable*> otherObjects;
	Collideable* temp;

	for (int i = 0; i < m_pEngine->GetArraySize(); ++i) {
		if ((temp = dynamic_cast<Collideable*>(m_pEngine->GetDisplayableObject(i))) != NULL && temp != object) {
			//if (temp->GetIsCollideable())
			otherObjects.push_back(temp);
		}
	}

	for (std::vector<Collideable*>::iterator it = otherObjects.begin(); it != otherObjects.end(); ++it) {
		(*it)->GetEdges(tempObjectEdges);
		if (IsInBounds(objectEdges[LEFT], objectEdges[TOP], tempObjectEdges) ||
			IsInBounds(objectEdges[RIGHT], objectEdges[TOP], tempObjectEdges) ||
			IsInBounds(objectEdges[LEFT], objectEdges[BOTTOM], tempObjectEdges) ||
			IsInBounds(objectEdges[LEFT], objectEdges[BOTTOM], tempObjectEdges))
			return true;
	}

	return false;
}

void Psydb3CollisionHandler::GetTileEdges(int tileMapX, int tileMapY, int edges[4]) {
	edges[LEFT] = tileMapX*m_map->GetTileWidth();
	edges[TOP] = tileMapY*m_map->GetTileHeight();
	edges[RIGHT] = edges[LEFT] + m_map->GetTileWidth();
	edges[BOTTOM] = edges[TOP] + m_map->GetTileHeight();
}


bool Psydb3CollisionHandler::IsInBounds(int x, int y, int edges[4]) {
	return (x >= edges[LEFT]) && (x <= edges[RIGHT]) && (y >= edges[TOP]) && (y <= edges[BOTTOM]);
}
