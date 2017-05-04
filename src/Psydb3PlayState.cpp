#include "Psydb3PlayState.h"
#include <iostream>

#include "Psydb3PlayerTank.h"
#include "Psydb3Cursor.h"
#include "Psydb3Bomb.h"

Psydb3PlayState::Psydb3PlayState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine)
	, m_mapFilePath("MapData/maps.txt")
	, m_level(0)
	, m_backgroundInitialised(false) {
	GetMaps();
}

void Psydb3PlayState::InitialiseObjects() {
	m_pEngine->CreateObjectArray(4);
	m_pEngine->StoreObjectInArray(0, new Psydb3Bomb(m_pEngine, m_pEngine->GetTime(), 500, 500));
	m_pEngine->StoreObjectInArray(1, new Psydb3PlayerTank(m_pEngine, 500.0, 500.0));
	m_pEngine->StoreObjectInArray(2, new Psydb3Cursor(m_pEngine));
	m_pEngine->StoreObjectInArray(3, NULL);

	m_pEngine->SetAllVisibility(false);

	m_collisionHandler = new Psydb3CollisionHandler(m_pEngine, &m_oTiles);
}


Psydb3PlayState::~Psydb3PlayState() {
	delete m_collisionHandler;
}

void Psydb3PlayState::DrawBackground() {
	//also think about bombs with iCurrentTime, as if paused will continue to time towards explode

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

		m_backgroundInitialised = true;
	}
	else {
		for (int i = 0; i < m_pEngine->GetScreenWidth(); ++i) {
			for (int j = 0; j < m_pEngine->GetScreenHeight(); ++j) {
				m_pEngine->SafeSetBackgroundPixel(i, j, m_map.at(i).at(j));
			}
		}
	}

	for (int j = 0; j < 18; ++j) {
		for (int i = 0; i < 28; ++i) {
			char temp = (m_oTiles.IsTileCollideable(i, j)) ? 'y' : 'n';
			printf("%c",temp);
		}
		printf("\n");
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

void Psydb3PlayState::Update() {
	m_pEngine->UpdateAllObjects(m_pEngine->GetModifiedTime());
	m_collisionHandler->Update();
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
			SaveBackground();
			m_pEngine->SetState(PAUSE_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(false);
			break;
	}
}