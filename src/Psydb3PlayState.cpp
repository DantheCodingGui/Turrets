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
	, m_level(3)
	, m_numberOfTanks(0)
	, m_backgroundInitialised(false) {
	m_startTime = pEngine->GetTime();
	GetMaps();
	GetTankNames();
	m_collisionHandler = new Psydb3CollisionHandler(m_pEngine, &m_oTiles);
}

void Psydb3PlayState::InitialiseObjects() {

	srand(time(NULL));

	m_numberOfTanks = 5;
	m_bulletManager = new Psydb3BulletManager(m_pEngine, m_numberOfTanks * 3);
	int i;
	m_pEngine->CreateObjectArray(m_numberOfTanks * 4 + 1);
	for (i = 0; i < m_numberOfTanks * 3; ++i)
		m_pEngine->StoreObjectInArray(i, new Psydb3Bullet(m_pEngine, m_collisionHandler));
	m_pEngine->StoreObjectInArray(i, new Psydb3InvisibleEnemyTank(m_pEngine, 1350.0, 400.0, m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str()));
	m_pEngine->StoreObjectInArray(i + 1, new Psydb3AdvancedEnemyTank(m_pEngine, 900.0, 400.0, m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str()));
	m_pEngine->StoreObjectInArray(i + 2, new Psydb3StandardEnemyTank(m_pEngine, 1200.0, 300.0, m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str()));
	m_pEngine->StoreObjectInArray(i + 3, new Psydb3BasicEnemyTank(m_pEngine, 1200.0, 500.0, m_collisionHandler, m_bulletManager, m_tankNames[rand() % (m_tankNames.size() - 1)].c_str()));
	m_pEngine->StoreObjectInArray(i + 4, new Psydb3PlayerTank(m_pEngine, 500.0, 500.0, m_collisionHandler, m_bulletManager, "Challenger"));
	m_pEngine->StoreObjectInArray(i + 5, new Psydb3Cursor(m_pEngine));

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

void Psydb3PlayState::GetTankSpawns() {
	vector<string> tankSpawnData;
	m_fileHandler.ReadTextFile(&tankSpawnData, "MapData/tank_spawns.txt");
	return;
	vector<string> spawns;
	for (int i = 3; i < m_maps.size(); ++i) {
		for (int j = 0; spawns[i] != "" && spawns[i] != "END"; ++i, j++) {
			spawns.push_back(spawns[i]);
		}
		m_maps.push_back(spawns);
		spawns.clear();
	}
}

void Psydb3PlayState::LoadLevel() {
	m_backgroundInitialised = false;
	//m_pEngine->DestroyOldObjects();

	//get length of spawns for level number, plug into function below

	//m_pEngine->CreateObjectArray(5);
	//for loop for bullets
	//for loop for tanks, switch statement to decide what object to display there
	//at index i, player tank
	//at index i + 1, cursor
	DrawBackground();
}

void Psydb3PlayState::GetTankNames() {
	m_fileHandler.ReadTextFile(&m_tankNames, "TankNames/names.txt");
}

void Psydb3PlayState::Update() {
	if (HasLevelStarted())
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
		case SDLK_1:
			m_level = 0;
			LoadLevel();
			break;
		case SDLK_2:
			m_level = 1;
			LoadLevel();
			break;
		case SDLK_3:
			m_level = 2;
			LoadLevel();
			break;
		case SDLK_4:
			m_level = 3;
			LoadLevel();
			break;
	}
}

void Psydb3PlayState::HandleMouse() {
	dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(m_pEngine->GetArraySize() - 2))->SetFiring(true);
}

void Psydb3PlayState::DrawOntop() {

	if (!HasLevelStarted()) {
		char buffer[20];
		m_pEngine->DrawScreenString(600, 350, "Are You Ready??", 0xffffff, m_pEngine->GetFont("Blockletter.otf", 70));
		sprintf(buffer, "Are You Ready?? in");
		m_pEngine->DrawScreenString(600, 350, buffer, 0xffffff, m_pEngine->GetFont("Blockletter.otf", 70));
		return;
	}

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

void Psydb3PlayState::UnDrawStrings() {
	m_pEngine->CopyBackgroundPixels(600, 350, 600, 200);

	Psydb3Tank* temp;
	for (int i = 0; i < m_pEngine->GetArraySize(); ++i) {
		if ((temp = dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(i))) != NULL)
			m_pEngine->CopyBackgroundPixels(
				temp->GetXCentre() - 40,
				temp->GetYCentre() - 70, 80, 20);
	}
}