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
			pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0xdcbc7f, pSurface);
			break;
		case WALL_TILE:
		case WALL_TILE_ONLY_TOP:
			if (tileType == WALL_TILE)
				pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				0x8C7640, pSurface);
			pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				0xE9C977, pSurface);
			
			break;
		case TALL_WALL_TILE: 
		case TALL_WALL_TILE_ONLY_TOP:
			if (tileType == TALL_WALL_TILE) {
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + GetTileHeight() - 1,
					0x8C7640, pSurface);
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20,
					0xE9C977, pSurface);
			}
			else {
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + 10,
					0x8C7640, pSurface);
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20,
					0xE9C977, pSurface);
			}
			break;
		case BREAKABLE_WALL_TILE: 
		case BREAKABLE_WALL_TILE_ONLY_TOP:
			if (tileType == BREAKABLE_WALL_TILE) 
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY + 10,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + GetTileHeight() - 1,
					0x8C7640, pSurface);
			pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				0xE9C977, pSurface);
			
			if (tileType == BREAKABLE_WALL_TILE) {
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + 20,
					iStartPositionScreenY + 15,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + 15,
					iStartPositionScreenY + GetTileHeight() - 10,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY + GetTileHeight() - 10,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + 5,
					iStartPositionScreenY + 10,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + 10,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 20,
					iStartPositionScreenY + GetTileHeight() - 15,
					iStartPositionScreenX + 5,
					iStartPositionScreenY + GetTileHeight() - 1,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + GetTileHeight() - 1,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth()/2 ,
					iStartPositionScreenY + 10,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + 10,
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					iStartPositionScreenX + 20,
					iStartPositionScreenY - 20,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY - 10,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY - 10,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 5,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + 10,
					iStartPositionScreenX + GetTileWidth() - 10,
					iStartPositionScreenY,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth()/2,
					iStartPositionScreenY + 10,
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 2,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY - 9,
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 20,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() -5,
					iStartPositionScreenY - 29,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY - 30,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX,
					iStartPositionScreenY - 12,
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					0x6F5744, pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					iStartPositionScreenX + 3,
					iStartPositionScreenY - 30,
					0x6F5744, pSurface);
				
			}
			break;
	}
}

void Psydb3TileManager::RemoveTile(BaseEngine* pEngine, int x, int y) {
	UpdateTile(pEngine, x, y, FLOOR_TILE);
	pEngine->DrawScreenRectangle(x*m_iTileWidth, y*m_iTileHeight + 10 - m_iTileHeight, x*m_iTileWidth + m_iTileWidth, y*m_iTileHeight + 10, 0xdcbc7f);
	pEngine->DrawBackgroundRectangle(x*m_iTileWidth, y*m_iTileHeight + 10 - m_iTileHeight, x*m_iTileWidth + m_iTileWidth, y*m_iTileHeight + 10, 0xdcbc7f);
	int tileBehindValue = GetValue(x, y - 1);
	if (tileBehindValue > BREAKABLE_WALL_TILE) {
		UpdateTile(pEngine, x, y - 1, tileBehindValue - 3);
	}
}