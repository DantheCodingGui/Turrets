#include "Psydb3TileManager.h"
#include "header.h"
#include "JPGImage.h"

Psydb3TileManager::Psydb3TileManager()
	: TileManager(40, 60)
	, m_collidableWallOffset(20)
	, m_currentColourSet(0){

	std::vector<unsigned int> temp;

	temp.push_back(0xDCBC7F);
	temp.push_back(0x8C7640);
	temp.push_back(0xE9C977);
	temp.push_back(0x6F5744);
	temp.push_back(0xD3AA5F);
	m_mapColours.push_back(temp);
	temp.clear();

	temp.push_back(0x336600);
	temp.push_back(0x666666);
	temp.push_back(0xCCCCCC);
	temp.push_back(0x333333);
	temp.push_back(0x996633);
	m_mapColours.push_back(temp);
	temp.clear();

	temp.push_back(0xffffff);
	temp.push_back(0xCCCCCC);
	temp.push_back(0xF2F2F2);
	temp.push_back(0xBFBFBF);
	temp.push_back(0xBFBFBF);
	m_mapColours.push_back(temp);
	temp.clear();

	temp.push_back(0x4D0F00);
	temp.push_back(0x330A00);
	temp.push_back(0x801A00);
	temp.push_back(0xFF3300);
	temp.push_back(0xCC2900);
	m_mapColours.push_back(temp);
	temp.clear();

	temp.push_back(0x009900);
	temp.push_back(0x003300);
	temp.push_back(0x00B300);
	temp.push_back(0x001A00);
	temp.push_back(0x00B300);
	m_mapColours.push_back(temp);
	temp.clear();

	RandomiseMapColour();

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
				m_mapColours[m_currentColourSet][0], pSurface);
			break;
		case WALL_TILE:
		case WALL_TILE_ONLY_TOP:
			if (tileType == WALL_TILE)
				pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10,
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + GetTileHeight() - 1,
				m_mapColours[m_currentColourSet][1], pSurface);
			pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				m_mapColours[m_currentColourSet][2], pSurface);
			
			break;
		case TALL_WALL_TILE: 
		case TALL_WALL_TILE_ONLY_TOP:
			if (tileType == TALL_WALL_TILE) {
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + GetTileHeight() - 1,
					m_mapColours[m_currentColourSet][1], pSurface);
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20,
					m_mapColours[m_currentColourSet][2], pSurface);
			}
			else {
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY + 10,
					m_mapColours[m_currentColourSet][1], pSurface);
				pEngine->DrawRectangle(
					iStartPositionScreenX,
					iStartPositionScreenY - 20 - GetTileHeight(),
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 20,
					m_mapColours[m_currentColourSet][2], pSurface);
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
					m_mapColours[m_currentColourSet][1], pSurface);
			pEngine->DrawRectangle(
				iStartPositionScreenX,
				iStartPositionScreenY + 10 - GetTileHeight(),
				iStartPositionScreenX + GetTileWidth() - 1,
				iStartPositionScreenY + 10 - 1,
				m_mapColours[m_currentColourSet][2], pSurface);
			
			if (tileType == BREAKABLE_WALL_TILE) {
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + 20,
					iStartPositionScreenY + 15,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + 15,
					iStartPositionScreenY + GetTileHeight() - 10,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + GetTileHeight() / 2 + 5,
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY + GetTileHeight() - 10,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + 5,
					iStartPositionScreenY + 10,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + 10,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 20,
					iStartPositionScreenY + GetTileHeight() - 15,
					iStartPositionScreenX + 5,
					iStartPositionScreenY + GetTileHeight() - 1,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + GetTileHeight() - 1,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY + 15,
					iStartPositionScreenX + GetTileWidth()/2 ,
					iStartPositionScreenY + 10,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY + 10,
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					iStartPositionScreenX + 20,
					iStartPositionScreenY - 20,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY - 10,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 20,
					iStartPositionScreenY - 10,
					iStartPositionScreenX + GetTileWidth() - 1,
					iStartPositionScreenY - 5,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 5,
					iStartPositionScreenY + 10,
					iStartPositionScreenX + GetTileWidth() - 10,
					iStartPositionScreenY,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth()/2,
					iStartPositionScreenY + 10,
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 2,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY - 9,
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 20,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() -5,
					iStartPositionScreenY - 29,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + GetTileWidth() - 15,
					iStartPositionScreenY - 20,
					iStartPositionScreenX + GetTileWidth() / 2,
					iStartPositionScreenY - 30,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX,
					iStartPositionScreenY - 12,
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					m_mapColours[m_currentColourSet][3], pSurface);
				pEngine->DrawLine(
					iStartPositionScreenX + 15,
					iStartPositionScreenY - 5,
					iStartPositionScreenX + 3,
					iStartPositionScreenY - 30,
					m_mapColours[m_currentColourSet][3], pSurface);
				
			}
			break;
	}
}

void Psydb3TileManager::RemoveTile(BaseEngine* pEngine, int x, int y) {
	UpdateTile(pEngine, x, y, FLOOR_TILE);
	pEngine->DrawScreenRectangle(x*m_iTileWidth, y*m_iTileHeight + 10 - m_iTileHeight, x*m_iTileWidth + m_iTileWidth, y*m_iTileHeight + 10, m_mapColours[m_currentColourSet][0]);
	pEngine->DrawBackgroundRectangle(x*m_iTileWidth, y*m_iTileHeight + 10 - m_iTileHeight, x*m_iTileWidth + m_iTileWidth, y*m_iTileHeight + 10, m_mapColours[m_currentColourSet][0]);
	int tileBehindValue = GetValue(x, y - 1);
	if (tileBehindValue > BREAKABLE_WALL_TILE) {
		UpdateTile(pEngine, x, y - 1, tileBehindValue - 3);
	}
}