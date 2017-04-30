#include "Psydb3PlayState.h"
#include <iostream>

Psydb3PlayState::Psydb3PlayState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine)
	, m_mapFilePath("MapData/maps.txt")
	, m_level(1) {
	GetMaps();
	SDL_ShowCursor(SDL_DISABLE); //disable the mouse icon while playing
}


Psydb3PlayState::~Psydb3PlayState() {
}

void Psydb3PlayState::SetupBackgroundBuffer() {
	//also think about bombs with iCurrentTime, as if paused will continue to time towards explode

	m_oTiles.SetSize(28, 18);

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 18; ++j)
			m_oTiles.SetValue(i, j, m_maps[m_level][j][i] - 'a');
	}
	m_oTiles.SetBaseTilesPositionOnScreen(0, 0);

	m_oTiles.DrawAllTiles(m_pEngine,
		m_pEngine->GetBackground(),
		0, 0, 27, 17);
}

void Psydb3PlayState::GetMaps() {
	vector<string> mapData;
	m_fileHandler.ReadTextFile(&mapData, m_mapFilePath);

	vector<string> map;
	for (int i = 3; i < (stoi(mapData[0])*stoi(mapData[1])); ++i) {
		for (int j = 0; mapData[i] != "" && mapData[i] != "END"; ++i, j++) {
			map.push_back(mapData[i]);
			//cout << mapData[i] << endl;
		}
		m_maps.push_back(map);
		map.clear();
		//cout << "\n" << endl;
	}
}

void Psydb3PlayState::Update() {
	m_pEngine->UpdateAllObjects(m_pEngine->GetModifiedTime());
}

void Psydb3PlayState::HandleKeys(int iKeyCode) {
	
	switch (iKeyCode) {
		case SDLK_p:
			m_pEngine->SetState(PAUSE_STATE);
			m_pEngine->UndrawObjects();
			break;
	}
}