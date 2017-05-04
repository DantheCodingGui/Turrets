#include "Psydb3CollisionHandler.h"
#include "header.h"
#include "templates.h"
#include <vector>

Psydb3CollisionHandler::Psydb3CollisionHandler(Psydb3Engine* pEngine, Psydb3TileManager* tileManager) 
	: m_pEngine(pEngine)
	, m_map(tileManager) {

	std::vector<Collideable*> collideableObjects;
	int i;
	int endOfArray = m_pEngine->GetArraySize();
	for (i = 0; i < endOfArray; ++i) {
		Collideable* temp;
		if ((temp = dynamic_cast<Collideable*>(m_pEngine->GetDisplayableObject(i))) != NULL)
			collideableObjects.push_back(temp);
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
}

Psydb3CollisionHandler::~Psydb3CollisionHandler() {
}

void Psydb3CollisionHandler::Update() {
	BackgroundCollision();
	//ObjectCollision();
}

char Psydb3CollisionHandler::BackgroundCollision() {
	bool collision = false;
	int tilesHorizontal = m_pEngine->GetScreenWidth() / m_map->GetTileWidth();
	int tilesVertical = m_pEngine->GetScreenHeight() / m_map->GetTileHeight();

	//for every tank, scan whole background for tile collisions
	for (int i = 0; i < m_tanks.size(); ++i) {

		int tankLeftEdge = (int)m_tanks[i]->GetX();
		int tankRightEdge = tankLeftEdge + m_tanks[i]->GetWidth();
		int tankTopEdge = (int)m_tanks[i]->GetY();
		int tankBottomEdge = tankTopEdge + m_tanks[i]->GetHeight();

		//4 tiles behind the player, ensures minimum checks per tank occur
		int adjacentTilePosLeft = tankLeftEdge / m_map->GetTileWidth();
		int adjacentTilePosRight = tankRightEdge / m_map->GetTileWidth();
		int adjacentTilePosTop = tankTopEdge / m_map->GetTileHeight();
		int adjacentTilePosBottom = tankBottomEdge / m_map->GetTileHeight();

		for (int j = adjacentTilePosLeft; j <= adjacentTilePosRight; ++j) {
			for (int k = adjacentTilePosTop; k <= adjacentTilePosBottom; ++k) {
				if (m_map->IsTileCollideable(j, k)) {
					collision = true;
					printf("collision!!!\n");
					return 'a';
				}
			}
		}

		/*
		for (int j = 0; j < tilesHorizontal; ++j) {
			for (int k = 0; k < tilesVertical; ++k) {
				if (m_map->IsTileCollideable(j, k)) {
					bool xOverlap = (tankLeftEdge < (m_map->GetTileWidth() * (j + 1)) && (tankRightEdge > (m_map->GetTileWidth() * j )) );
					bool yOverlap = (tankTopEdge < (m_map->GetTileHeight() * (k + 1)) && (tankBottomEdge > (m_map->GetTileHeight() * k )) );
					if (xOverlap && yOverlap) {
						collision = true;
						printf("collision!!!\n");
						return 'a';
					}
				}
			}
		}
		*/
	}
	printf("no collisions found\n");
	return 'b';
}

//unsigned char Psydb3CollisionHandler::DoesCollide() {

//}