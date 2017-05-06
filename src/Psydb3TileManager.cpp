#include "Psydb3TileManager.h"
#include "header.h"
#include "JPGImage.h"

Psydb3TileManager::Psydb3TileManager()
	: TileManager(40, 60)
	, m_collidableWallOffset(20) {
}


Psydb3TileManager::~Psydb3TileManager() {
}


void Psydb3TileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const {

	switch (GetValue(iMapX, iMapY)) {
		case FLOOR_TILE: 
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xdcbc7f);
			break;
		case WALL_TILE:


		/*	pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() -1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xE9C977);
			*/
			
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x8C7640);
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				0xE9C977);
			
			break;
		case TALL_WALL_TILE: 
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY - 20,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x8C7640);
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY - 20 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY - 20 - 1,
				0xE9C977);
			break;
		case BREAKABLE_WALL_TILE: 
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x9F7D61);
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				0xE3B28A);

			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + GetTileWidth()/2, 
				iStartPositionScreenY + GetTileHeight()/2 + 5, 
				iStartPositionScreenX + 20, 
				iStartPositionScreenY + 15, 
				0x6F5744);
			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + GetTileWidth() / 2,
				iStartPositionScreenY + GetTileHeight() / 2 + 5,
				iStartPositionScreenX + GetTileWidth() - 20,
				iStartPositionScreenY + 15,
				0x6F5744);
			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + GetTileWidth() / 2,
				iStartPositionScreenY + GetTileHeight() / 2 + 5,
				iStartPositionScreenX + 15,
				iStartPositionScreenY + GetTileHeight() - 10,
				0x6F5744);
			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + GetTileWidth() / 2,
				iStartPositionScreenY + GetTileHeight() / 2 + 5,
				iStartPositionScreenX + GetTileWidth() - 15,
				iStartPositionScreenY + GetTileHeight() - 10,
				0x6F5744);
			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + 20,
				iStartPositionScreenY + 15,
				iStartPositionScreenX + 5,
				iStartPositionScreenY + 10,
				0x6F5744);
			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + GetTileWidth() - 20,
				iStartPositionScreenY + 15,
				iStartPositionScreenX + GetTileWidth() - 5,
				iStartPositionScreenY + 10,
				0x6F5744);
			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + 20,
				iStartPositionScreenY + GetTileHeight() - 15,
				iStartPositionScreenX + 5,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x6F5744);
			pEngine->DrawBackgroundLine(
				iStartPositionScreenX + GetTileWidth() - 20,
				iStartPositionScreenY + 15,
				iStartPositionScreenX + GetTileWidth() - 5,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x6F5744);
			//DO CRACKS LATER
			break;
		case BREAKABLE_TALL_WALL_TILE:
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x9F7D61);
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				0xE3B28A);
			break;
	}
}

//used when an object is "behind"a tile, to uphold the illusion
void Psydb3TileManager::DrawForegroundTileAt(
	BaseEngine* pEngine,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const {
	switch (GetValue(iMapX, iMapY)) {
		case FLOOR_TILE:
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xdcbc7f);
			break;
		case WALL_TILE:
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x8C7640);
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				0xE9C977);

			break;
		case TALL_WALL_TILE:
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY - 20,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x8C7640);
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY - 20 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY - 20 - 1,
				0xE9C977);
			break;
		case BREAKABLE_WALL_TILE:
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x9F7D61);
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				0xE3B28A);
			break;
	}
}