#pragma once
#include "TileManager.h"
class Psydb3TileManager :
	public TileManager {
public:
	Psydb3TileManager();
	~Psydb3TileManager();
	void Psydb3TileManager::DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

