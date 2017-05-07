#pragma once
#include "TileManager.h"

#define FLOOR_TILE							0
#define WALL_TILE							1
#define TALL_WALL_TILE						2
#define BREAKABLE_WALL_TILE					3
#define BREAKABLE_TALL_WALL_TILE			4
#define WALL_TILE_ONLY_TOP					5
#define TALL_WALL_TILE_ONLY_TOP				6
#define BREAKABLE_WALL_TILE_ONLY_TOP		7
#define BREAKABLE_TALL_WALL_TILE_ONLY_TOP	8

class Psydb3TileManager :
	public TileManager {
public:
	Psydb3TileManager();
	~Psydb3TileManager();
	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
	void DrawForegroundTileAt(
		BaseEngine* pEngine,
		int iMapX, int iMapY) const;
	int GetCollisionOffset() const { return m_collidableWallOffset; };
	//true for anything not a floor tile
	bool IsTileCollideable(int x, int y) { return (GetValue(x, y) != FLOOR_TILE) ? true : false; };
	int IsTileBehindWall(int x, int y) {
		if (GetValue(x, y + 1) != FLOOR_TILE)
			return 1;
		else if (GetValue(x, y + 2) != FLOOR_TILE)
			return 2;
		return -1;
	};
	std::vector<int> m_tilesToRedrawX;
	std::vector<int> m_tilesToRedrawY;
private:
	int m_collidableWallOffset;
};


