#pragma once
#include "TileManager.h"
#include <cmath>
#include <ctime>

#define FLOOR_TILE							0
#define WALL_TILE							1
#define TALL_WALL_TILE						2
#define BREAKABLE_WALL_TILE					3
#define WALL_TILE_ONLY_TOP					5
#define TALL_WALL_TILE_ONLY_TOP				6
#define BREAKABLE_WALL_TILE_ONLY_TOP		7

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
	//true for anything not a floor tile
	bool IsTileCollideable(int x, int y) { return (GetValue(x, y) != FLOOR_TILE) ? true : false; };
	bool IsTileBreakable(int x, int y) { 
		int value = GetValue(x, y);
		return (value == BREAKABLE_WALL_TILE 
			|| value == BREAKABLE_WALL_TILE_ONLY_TOP) ? true : false;
	};
	void RemoveTile(BaseEngine* pEngine, int x, int y);
	int IsTileBehindWall(int x, int y) {
		if (GetValue(x, y + 1) != FLOOR_TILE)
			return 1;
		if (y + 1 == m_iMapHeight)
			return 1;
		if (GetValue(x, y + 2) != FLOOR_TILE)
			return 2;
		return -1;
	};
	void RandomiseMapColour() { srand(time(NULL)); m_currentColourSet = rand() % (m_mapColours.size() - 1); };
	unsigned int GetMapColour(int index) const { return m_mapColours[m_currentColourSet][index]; };
	std::vector<int> m_tilesToRedrawX;
	std::vector<int> m_tilesToRedrawY;
private:
	int m_collidableWallOffset;

	int m_currentColourSet;

	std::vector<std::vector<unsigned int>> m_mapColours;
};


