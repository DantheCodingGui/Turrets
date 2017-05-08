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

	int tileType = GetValue(iMapX, iMapY);
	switch (tileType) {
		case FLOOR_TILE: 
			pEngine->DrawBackgroundRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xdcbc7f);
			break;
		case WALL_TILE:
		case WALL_TILE_ONLY_TOP:
			if (tileType == WALL_TILE)
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
		case TALL_WALL_TILE_ONLY_TOP:
			if (tileType == TALL_WALL_TILE) {
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
					iStartPositionScreenY - 20,
					0xE9C977);
			}
			else {
				pEngine->DrawBackgroundRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + 10,
					0x8C7640);
				pEngine->DrawBackgroundRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20 - 1,
					0xE9C977);
			}
			break;
		case BREAKABLE_WALL_TILE: 
		case BREAKABLE_WALL_TILE_ONLY_TOP:
			if (tileType == BREAKABLE_WALL_TILE) 
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
			
			if (tileType == BREAKABLE_WALL_TILE) {
				pEngine->DrawBackgroundLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
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
			}
			break;
		case BREAKABLE_TALL_WALL_TILE:
		case BREAKABLE_TALL_WALL_TILE_ONLY_TOP:
			if (tileType == BREAKABLE_TALL_WALL_TILE)
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
			if (tileType == BREAKABLE_TALL_WALL_TILE) {
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
			}
			else {
				pEngine->DrawBackgroundRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + 10,
					0x8C7640);
				pEngine->DrawBackgroundRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20 - 1,
					0xE9C977);
			}
	}
}

//used when an object is "behind"a tile, to uphold the illusion
void Psydb3TileManager::DrawForegroundTileAt(
	BaseEngine* pEngine,
	int iMapX, int iMapY) const {

	int iStartPositionScreenX = iMapX*m_iTileWidth;
	int iStartPositionScreenY = iMapY*m_iTileHeight;

	int tileType = GetValue(iMapX, iMapY);
	switch (tileType) {
		case FLOOR_TILE:
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xdcbc7f);
			break;
		case WALL_TILE:
		case WALL_TILE_ONLY_TOP:
			if (tileType == WALL_TILE)
				pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth(),
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
		case TALL_WALL_TILE_ONLY_TOP:
			if (tileType == TALL_WALL_TILE) {
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
			}
			else {
				pEngine->DrawScreenRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + 10,
					0x8C7640);
				pEngine->DrawScreenRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20 - 1,
					0xE9C977);
			}
			break;
		case BREAKABLE_WALL_TILE:
		case BREAKABLE_WALL_TILE_ONLY_TOP:
			if (tileType == BREAKABLE_WALL_TILE)
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

			if (tileType == BREAKABLE_WALL_TILE) {
				pEngine->DrawScreenLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + 20,
					iStartPositionScreenY + 15,
					0x6F5744);
				pEngine->DrawScreenLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					0x6F5744);
				pEngine->DrawScreenLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + 15,
					iStartPositionScreenY + GetTileHeight() - 10,
					0x6F5744);
				pEngine->DrawScreenLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY + GetTileHeight() - 10,
					0x6F5744);
				pEngine->DrawScreenLine(
					iStartPositionScreenX + 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + 5,
					iStartPositionScreenY + 10,
					0x6F5744);
				pEngine->DrawScreenLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + 10,
					0x6F5744);
				pEngine->DrawScreenLine(
					iStartPositionScreenX + 20,
					iStartPositionScreenY + GetTileHeight() - 15,
					iStartPositionScreenX + 5,
					iStartPositionScreenY + GetTileHeight() - 1,
					0x6F5744);
				pEngine->DrawScreenLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + GetTileHeight() - 1,
					0x6F5744);
				//DO CRACKS LATER
			}
			break;
		case BREAKABLE_TALL_WALL_TILE:
		case BREAKABLE_TALL_WALL_TILE_ONLY_TOP:
			if (tileType == BREAKABLE_TALL_WALL_TILE)
				pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x8C7640);
			pEngine->DrawScreenRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth(),
				iStartPositionScreenY + 10 - 1,
				0xE9C977);
			break;
			if (tileType == BREAKABLE_TALL_WALL_TILE) {
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
			}
			else {
				pEngine->DrawScreenRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + 10,
					0x8C7640);
				pEngine->DrawScreenRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20 - 1,
					0xE9C977);
			}
	}
}

void Psydb3TileManager::RemoveTile(BaseEngine* pEngine, int x, int y) {
	SetValue(x, y, FLOOR_TILE);
	DrawTileAt(pEngine, pEngine->GetBackground(), x, y, x*m_iTileWidth, y*m_iTileHeight);
	DrawForegroundTileAt(pEngine, x, y);
	pEngine->DrawScreenRectangle(x*m_iTileWidth, y*m_iTileHeight + 10 - m_iTileHeight, x*m_iTileWidth + m_iTileWidth, y*m_iTileHeight + 10, 0xdcbc7f);
	pEngine->DrawBackgroundRectangle(x*m_iTileWidth, y*m_iTileHeight + 10 - m_iTileHeight, x*m_iTileWidth + m_iTileWidth, y*m_iTileHeight + 10, 0xdcbc7f);
	int tileBehindValue = GetValue(x, y - 1);
	if (tileBehindValue > BREAKABLE_TALL_WALL_TILE) {
		printf("old value: %d, new value: %d\n", tileBehindValue, tileBehindValue );
		SetValue(x, y - 1, tileBehindValue - 4);
		DrawTileAt(pEngine, pEngine->GetBackground(), x, y - 1, x*m_iTileWidth, (y - 1)*m_iTileHeight);
		DrawForegroundTileAt(pEngine, x, y - 1);
	}
}