#pragma once
#include "Psydb3Engine.h"
#include "Psydb3TileManager.h"
#include "Psydb3Tank.h"

class Psydb3CollisionHandler
{
public:
	Psydb3CollisionHandler(Psydb3Engine* pEngine, Psydb3TileManager* tileManager);
	~Psydb3CollisionHandler();
	bool CheckBackgroundCollision(Collideable* object);
	int CheckObjectsCollision(Collideable* object);
	void GetTileEdges(int tileMapX, int tileMapY, int edges[4]);
	bool IsInBounds(int x, int y, int edges[4]);
private:
	Psydb3TileManager* m_map;

	Psydb3Engine* m_pEngine;
};

