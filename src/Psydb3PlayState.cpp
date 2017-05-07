#include "Psydb3PlayState.h"
#include <iostream>
#include <ctime>

#include "Psydb3PlayerTank.h"
#include "Psydb3Cursor.h"
#include "Psydb3Bomb.h"
#include "Psydb3Bullet.h"

Psydb3PlayState::Psydb3PlayState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine)
	, m_mapFilePath("MapData/maps.txt")
	, m_level(3)
	, m_backgroundInitialised(false) {
	GetMaps();
	GetTankNames();
	m_collisionHandler = new Psydb3CollisionHandler(m_pEngine, &m_oTiles);
}

void Psydb3PlayState::InitialiseObjects() {

	srand(time(NULL));
	


	int numberOfTanks = 1;
	m_bulletManager = new Psydb3BulletManager(m_pEngine, numberOfTanks*3);
	int i;
	m_pEngine->CreateObjectArray(numberOfTanks*4 + 1);
	for (i = 0; i < numberOfTanks*3; ++i) 
		m_pEngine->StoreObjectInArray(i, new Psydb3Bullet(m_pEngine, m_collisionHandler));
	m_pEngine->StoreObjectInArray(i, new Psydb3PlayerTank(m_pEngine, 500.0, 500.0, m_collisionHandler, m_bulletManager, "The Challenger"));
	m_pEngine->StoreObjectInArray(i + 1, new Psydb3Cursor(m_pEngine));

	m_pEngine->SetAllVisibility(false);
}


Psydb3PlayState::~Psydb3PlayState() {
	delete m_collisionHandler;
	delete m_bulletManager;
}

void Psydb3PlayState::DrawBackground() {
	if (!m_backgroundInitialised) {
		m_oTiles.SetSize(28, 18);

		for (int i = 0; i < 28; ++i) {
			for (int j = 0; j < 18; ++j)
				m_oTiles.SetValue(i, j, m_maps[m_level][j][i] - 'a');
		}
		m_oTiles.SetBaseTilesPositionOnScreen(0, 0);

		m_oTiles.DrawAllTiles(m_pEngine,
			m_pEngine->GetBackground(),
			0, 0, 27, 17);

		char levelStringBuffer[10];
		sprintf(levelStringBuffer, "Level %d", m_level + 1);
		m_pEngine->DrawBackgroundString(100, 10, levelStringBuffer, 0x000000, m_pEngine->GetFont("Blockletter.otf", 30));

		m_backgroundInitialised = true;
	}
	else {
		for (int i = 0; i < m_pEngine->GetScreenWidth(); ++i) {
			for (int j = 0; j < m_pEngine->GetScreenHeight(); ++j) {
				m_pEngine->SafeSetBackgroundPixel(i, j, m_map.at(i).at(j));
			}
		}
	}
}

void Psydb3PlayState::GetMaps() {
	vector<string> mapData;
	m_fileHandler.ReadTextFile(&mapData, m_mapFilePath);

	vector<string> map;
	for (int i = 3; i < (stoi(mapData[0])*stoi(mapData[1])); ++i) {
		for (int j = 0; mapData[i] != "" && mapData[i] != "END"; ++i, j++) {
			map.push_back(mapData[i]);
		}
		m_maps.push_back(map);
		map.clear();
	}
}

void Psydb3PlayState::GetTankNames() {
	m_fileHandler.ReadTextFile(&m_tankNames, "TankNames/names.txt");
}

void Psydb3PlayState::Update() {
	m_pEngine->UpdateAllObjects(m_pEngine->GetModifiedTime());

	

}

void Psydb3PlayState::SaveBackground() {
	vector<unsigned int> tempMap;
	for (int i = 0; i < m_pEngine->GetScreenWidth(); ++i) {
		for (int j = 0; j < m_pEngine->GetScreenHeight(); ++j) {
			tempMap.push_back(m_pEngine->SafeGetBackgroundPixel(i, j));
		}
		m_map.push_back(tempMap);
		tempMap.clear();
	}
}

void Psydb3PlayState::HandleKeys(int iKeyCode) {
	
	switch (iKeyCode) {
		case SDLK_ESCAPE:
			m_map.clear();
			SaveBackground();
			m_pEngine->SetState(PAUSE_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(false);
			break;
	}
}

void Psydb3PlayState::HandleMouse() {
	dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(m_pEngine->GetArraySize() - 2))->SetFiring(true);
}

void Psydb3PlayState::DrawOntop() {

	for (int i = 0; i < m_oTiles.m_tilesToRedrawX.size(); ++i) {
		m_oTiles.DrawTileAt(
			m_pEngine, m_pEngine->GetBackground(), 
			m_oTiles.m_tilesToRedrawX[i], 
			m_oTiles.m_tilesToRedrawY[i], 
			m_oTiles.m_tilesToRedrawX[i]*m_oTiles.GetTileWidth(),
			m_oTiles.m_tilesToRedrawY[i]*m_oTiles.GetTileHeight());
		m_oTiles.DrawForegroundTileAt(m_pEngine, m_oTiles.m_tilesToRedrawX[i], m_oTiles.m_tilesToRedrawY[i]);
	}
	m_oTiles.m_tilesToRedrawX.clear();
	m_oTiles.m_tilesToRedrawY.clear();

	//update the cursor again so it redraws over any now foreground tile
	m_pEngine->GetDisplayableObject(m_pEngine->GetArraySize() - 1)->Draw();

}