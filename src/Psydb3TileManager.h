#pragma once
#include "TileManager.h"

#define FLOOR_TILE	0
#define WALL_TILE	1
#define TALL_WALL_TILE	2
#define BREAKABLE_WALL_TILE 3

class Psydb3TileManager :
	public TileManager {
public:
	Psydb3TileManager();
	~Psydb3TileManager();
	virtual void Psydb3TileManager::DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
	int GetCollisionOffset(int direction) const { return (direction == 2) ? m_collidableWallOffset : 0; };
	//true for anything not a floor tile
	bool IsTileCollideable(int x, int y) { return (GetValue(x, y) != FLOOR_TILE) ? true : false; };
private:
	int m_collidableWallOffset;
};


