#include "Psydb3PlayState.h"


Psydb3PlayState::Psydb3PlayState(BaseEngine* pEngine)
	: Psydb3State(pEngine) {
}


Psydb3PlayState::~Psydb3PlayState() {
}

void Psydb3PlayState::SetupBackgroundBuffer() {
	//need access to m_oTiles in engine
	//also think about bombs with iCurrentTime, as if paused will continue to time towards explode
		//m_gameState->SetupBackgroundBuffer();
	/*
	char* data[] = {
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	"abbbbbbccbbbbbbbbcbbbbbbbbca",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaacbbaaaaaaaaaba",
	"abaaaaaaaaaaaaaabaaaaaaaaaba",
	"abaaaaaaaaaaaaaabaaaaaaaaaba",
	"abaaaaaabcdbbaaaaaaaaaaaaaba",
	"acaaaaaaaaaaaaaaaaaaabaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaadaaaaaaaaaaaba",
	"abaaaaaaaaaaaadaaaaaaaaaaaba",
	"abaaaaaaaaaadcdaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abbbbbccbbbbbbbbbbbbbbcccbba" };
	*/
	std::vector<std::string> mapData;
	m_fileHandler.ReadTextFile(&mapData, "MapData/1.txt");

	/*char* data[] = { //for testing tank motion
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	"abbbbbbccbbbbbbbbcbbbbbbbbca",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"acaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abaaaaaaaaaaaaaaaaaaaaaaaaba",
	"abbbbbccbbbbbbbbbbbbbbcccbba" };
	*/
	m_oTiles.SetSize(28, 18);

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 18; ++j)
			m_oTiles.SetValue(i, j, mapData[j][i] - 'a');
	}
	m_oTiles.SetBaseTilesPositionOnScreen(0, 0);

	m_oTiles.DrawAllTiles(m_pEngine,
		m_pEngine->GetBackground(),
		0, 0, 27, 17);
}