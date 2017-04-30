#pragma once
#include "Psydb3State.h"
#include "Psydb3TileManager.h"
#include "Psydb3FileIO.h"

class Psydb3PlayState :
	public Psydb3State
{
public:
	Psydb3PlayState(BaseEngine* pEngine);
	~Psydb3PlayState();
	virtual void SetupBackgroundBuffer();
	virtual bool ShouldAct() { return true; };
private:
	Psydb3TileManager m_oTiles;

	Psydb3FileIO m_fileHandler;
};

