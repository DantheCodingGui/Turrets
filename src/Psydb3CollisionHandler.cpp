#include "Psydb3CollisionHandler.h"
#include "header.h"
#include "templates.h"
#include <vector>

#define LEFT	0
#define TOP		1
#define RIGHT	2
#define BOTTOM	3
#define LEFT_TOP		4
#define RIGHT_TOP		5
#define LEFT_BOTTOM		6
#define RIGHT_BOTTOM	7

Psydb3CollisionHandler::Psydb3CollisionHandler(Psydb3Engine* pEngine, Psydb3TileManager* tileManager) 
	: m_pEngine(pEngine)
	, m_map(tileManager) {
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

	int tileWidth = m_map->GetTileWidth();
	int tileHeight = m_map->GetTileHeight();

	int objectEdges[4];

	object->GetEdges(objectEdges);

	int adjacentTilePosLeft = objectEdges[LEFT] / tileWidth;
	int adjacentTilePosRight = objectEdges[RIGHT] / tileWidth;
	int adjacentTilePosTop = objectEdges[TOP] / tileHeight;
	int adjacentTilePosBottom = objectEdges[BOTTOM] / tileHeight;

	for (int j = adjacentTilePosLeft; j <= adjacentTilePosRight; ++j) {
		for (int k = adjacentTilePosTop; k <= adjacentTilePosBottom; ++k) {
			if (m_map->IsTileCollideable(j, k)) {
				return true;
			}
		}
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