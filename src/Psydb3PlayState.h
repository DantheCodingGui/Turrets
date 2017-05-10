#pragma once
#include "Psydb3Engine.h"
#include "Psydb3State.h"
#include "Psydb3TileManager.h"
#include "Psydb3FileIO.h"
#include "Psydb3CollisionHandler.h"
#include <vector>
#include <string>

using namespace std;

class Psydb3PlayState :
	public Psydb3State
{
public:
	Psydb3PlayState(Psydb3Engine* pEngine);
	~Psydb3PlayState();
	virtual void DrawBackground();
	virtual void Update();
	virtual void HandleKeys(int iKeyCode);
	virtual void HandleMouse();
	virtual void DrawOntop();
	virtual void UnDrawStrings();
	void InitialiseObjects();
	void SaveBackground();
	void GetMaps();
	void GetTankSpawns();
	void LoadLevel();
	void GetTankNames();
	Psydb3Tank* GetPlayerTank() const { return dynamic_cast<Psydb3Tank*>(m_pEngine->GetDisplayableObject(m_pEngine->GetArraySize() - 2 - (m_numberOfTanks * 3))); };
	int GetNumberOfTanks() const { return m_numberOfTanks; };
	void NextLevel() {
		if (m_level != m_maps.size() - 1) 
			++m_level; 
	};
private:
	Psydb3TileManager m_oTiles;

	Psydb3FileIO m_fileHandler;

	vector<vector<string>> m_maps;
	vector<vector<string>> m_tankSpawns;

	int m_startCountdown;

	int m_level;
	int m_numberOfTanks;

	//used to decide whether to redraw background or reload saved version
	bool m_backgroundInitialised;
	//holds the background while pausing, needed to preserve background tracks
	vector<vector<unsigned int>> m_map;

	Psydb3CollisionHandler* m_collisionHandler;
	Psydb3BulletManager* m_bulletManager;

	vector<string> m_tankNames;
};

