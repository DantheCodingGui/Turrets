#include "Psydb3TileManager.h"
#include "header.h"

Psydb3TileManager::Psydb3TileManager()
	: TileManager(40, 60) {
}


Psydb3TileManager::~Psydb3TileManager() {
}

void Psydb3TileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const {

	switch (GetValue(iMapX, iMapY)) {
	case 0: //normal floor tile
		pEngine->DrawBackgroundRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			0xdcbc7f);
		break;
	case 1: //normal wall tile
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
	case 2: //tall wall tile
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
	case 3: //cork tile
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
	case 4: //cork tile w/ shadow (if you can get that)
		pEngine->DrawBackgroundRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY + GetTileHeight(),
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() + 10 - 1,
			0xBE9C70);
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