#include "Psydb3PlayState.h"
#include <iostream>
#include <ctime>

#include "Psydb3PlayerTank.h"
#include "Psydb3BasicEnemyTank.h"
#include "Psydb3StandardEnemyTank.h"
#include "Psydb3AdvancedEnemyTank.h"
#include "Psydb3InvisibleEnemyTank.h"
#include "Psydb3Cursor.h"
#include "Psydb3Bomb.h"
#include "Psydb3Bullet.h"

Psydb3PlayState::Psydb3PlayState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine)
	, m_level(1)
	, m_numberOfTanks(0)
	, m_startCountdown(300)
	, m_backgroundInitialised(false)
	, m_levelInitialised(false) {
	GetMaps();
	GetTankNames();
	m_collisionHandler = new Psydb3CollisionHandler(m_pEngine, &m_oTiles);
}

void Psydb3PlayState::InitialiseObjects() {
	LoadLevel();
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
	m_fileHandler.ReadTextFile(&mapData, "MapData/maps.txt");

	vector<string> map;
	for (int i = 3; i < (stoi(mapData[0])*stoi(mapData[1])); ++i) {
		for (int j = 0; mapData[i] != "" && mapData[i] != "END"; ++i, j++) {
			map.push_back(mapData[i]);
		}
		m_maps.push_back(map);
		map.clear();
	}
}

void Psydb3PlayState::LoadLevel() {
	
	srand(time(NULL));

	m_numberOfTanks = 3;
	m_bulletManager = new Psydb3BulletManager(m_pEngine, m_numberOfTanks * 3);
	int i;
	m_pEngine->CreateObjectArray(m_numberOfTanks * 4 + 1);

	for (i = 0; i < 2; ++i) {
		int tankToSpawn = rand() % 4;
		switch (tankToSpawn) {
			case(0) : {
						  m_pEngine->StoreObjectInArray(i, new Psydb3InvisibleEnemyTank(m_pEngine, 1100.0, 320.0 + (i*100), m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str(), &m_oTiles));
						  break;
			}
			case(1) : {
						  m_pEngine->StoreObjectInArray(i, new Psydb3AdvancedEnemyTank(m_pEngine, 1100.0, 320.0 + (i * 100), m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str(), &m_oTiles));
						  break;
			}
			case(2) : {
						  m_pEngine->StoreObjectInArray(i, new Psydb3StandardEnemyTank(m_pEngine, 1100.0, 320.0 + (i * 100), m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str(), &m_oTiles));
						  break;
			}
			case(3) : {
						  m_pEngine->StoreObjectInArray(i, new Psydb3BasicEnemyTank(m_pEngine, 1100.0, 320.0 + (i * 100), m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str(), &m_oTiles));
						  break;
			}
		}
	}
	m_pEngine->StoreObjectInArray(2, new Psydb3PlayerTank(m_pEngine, 400.0, 400.0, m_collisionHandler, m_bulletManager, "Challenger"));
	
	for (i = 0; i < m_numberOfTanks * 3; ++i)
		m_pEngine->StoreObjectInArray(i + m_numberOfTanks, new Psydb3Bullet(m_pEngine, m_collisionHandler));

	m_pEngine->StoreObjectInArray(i + m_numberOfTanks, new Psydb3Cursor(m_pEngine));

	m_oTiles.RandomiseMapColour();

 	for (i = 0; i < m_numberOfTanks; ++i)
		dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(i))->SetTracksColour(m_oTiles.GetMapColour(4));

	m_level = rand() & 6;
	m_startCountdown = 300;
	m_backgroundInitialised = false;
	m_levelInitialised = true;
	m_pEngine->SetupBackgroundBuffer();
	m_pEngine->Redraw(true);

}

void Psydb3PlayState::GetTankNames() {
	m_fileHandler.ReadTextFile(&m_tankNames, "TankNames/names.txt");
}

void Psydb3PlayState::Update() {
	if (!m_levelInitialised)
		LoadLevel();
	if (m_startCountdown == 0) {
		m_pEngine->UpdateAllObjects(m_pEngine->GetModifiedTime());
		if (!GetPlayerTank()->IsAlive()) {
			m_startCountdown = 300;
			m_pEngine->SetState(END_STATE);
			m_levelInitialised = false;
			m_backgroundInitialised = false; 
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
		}
		Psydb3EnemyTank* temp;
		bool nextLevel = true;
		for (int i = 0; i < m_numberOfTanks; ++i) {
			if ((temp = dynamic_cast<Psydb3EnemyTank*>(m_pEngine->GetDisplayableObject(i))) != NULL) {
				if (temp->IsAlive()) {
					nextLevel = false;
					break;
				}
			}
		}
		if (nextLevel)
			LoadLevel();
	}
	else
		--m_startCountdown;
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
			m_backgroundInitialised = false;
			SaveBackground();
			m_pEngine->SetState(PAUSE_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(false);
			break;
	}
}

void Psydb3PlayState::HandleMouse() {
	GetPlayerTank()->SetFiring(true);
}

void Psydb3PlayState::DrawOntop() {
	
	if (m_startCountdown > 0) {
		m_pEngine->DrawScreenString(600, 350, "Are You Ready??", 0x999999, m_pEngine->GetFont("Blockletter.otf", 70));
		return;
	}

	for (int i = 0; i < m_oTiles.m_tilesToRedrawX.size(); ++i) {
		m_oTiles.DrawTileAt(
			m_pEngine, m_pEngine->GetForeground(),
			m_oTiles.m_tilesToRedrawX[i],
			m_oTiles.m_tilesToRedrawY[i],
			m_oTiles.m_tilesToRedrawX[i] * m_oTiles.GetTileWidth(),
			m_oTiles.m_tilesToRedrawY[i] * m_oTiles.GetTileHeight());
		m_oTiles.DrawTileAt(
			m_pEngine, m_pEngine->GetBackground(),
			m_oTiles.m_tilesToRedrawX[i],
			m_oTiles.m_tilesToRedrawY[i],
			m_oTiles.m_tilesToRedrawX[i] * m_oTiles.GetTileWidth(),
			m_oTiles.m_tilesToRedrawY[i] * m_oTiles.GetTileHeight());
	}
	m_oTiles.m_tilesToRedrawX.clear();
	m_oTiles.m_tilesToRedrawY.clear();

	//removes bug of foreground tile drawing incorrectly at bottom of screen
	m_pEngine->DrawBackgroundRectangle(
		m_oTiles.GetTileWidth(),
		m_pEngine->GetScreenHeight() - m_oTiles.GetTileHeight() + 10,
		m_pEngine->GetScreenWidth() - m_oTiles.GetTileWidth(),
		m_pEngine->GetScreenHeight(),
		m_oTiles.GetMapColour(1));
	m_pEngine->CopyBackgroundPixels(
		m_oTiles.GetTileWidth(),
		m_pEngine->GetScreenHeight() - m_oTiles.GetTileHeight() + 10,
		m_pEngine->GetScreenWidth() - 2 * m_oTiles.GetTileWidth(),
		m_oTiles.GetTileHeight() - 10);

	//update the cursor again so it redraws over any now foreground tile
	m_pEngine->GetDisplayableObject(m_pEngine->GetArraySize() - 1)->Draw();
}

void Psydb3PlayState::UnDrawStrings() {
	m_pEngine->CopyBackgroundPixels(600, 350, 600, 200);

	Psydb3Tank* temp;
	for (int i = 0; i < m_pEngine->GetArraySize(); ++i) {
		if ((temp = dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(i))) != NULL)
			m_pEngine->CopyBackgroundPixels(
				temp->GetXCentre() - 40,
				temp->GetYCentre() - 70, 120, 20);
	}
}