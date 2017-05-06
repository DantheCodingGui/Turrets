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
	bool CheckObjectsCollision(Collideable* object);
	bool PixelPerfectCollision(Collideable* object, Collideable* otherObject);
	//unsigned char DoesCollide();
	void GetTileEdges(int tileMapX, int tileMapY, int edges[4]);
	bool IsInBounds(int x, int y, int edges[4]);
private:
	std::vector<Psydb3Tank*> m_tanks;
	//vector<Psydb3Bullet> bullets;

	Psydb3TileManager* m_map;

	Psydb3Engine* m_pEngine;

	unsigned int m_foregroundEmptyColour;
};

