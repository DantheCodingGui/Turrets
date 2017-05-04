#pragma once
#include "Psydb3Engine.h"
#include "Psydb3TileManager.h"
#include "Psydb3Tank.h"
class Psydb3CollisionHandler
{
public:
	Psydb3CollisionHandler(Psydb3Engine* pEngine, Psydb3TileManager* tileManager);
	~Psydb3CollisionHandler();
	void Update();
	char BackgroundCollision();
	//unsigned char DoesCollide();
private:
	std::vector<Psydb3Tank*> m_tanks;
	//vector<Psydb3Bullet> bullets;

	Psydb3TileManager* m_map;

	Psydb3Engine* m_pEngine;
};

