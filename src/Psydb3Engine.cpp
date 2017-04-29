#include "Psydb3Engine.h"
#include "header.h"

#include "Psydb3PlayerTank.h"
#include "Psydb3Cursor.h"
#include "Psydb3Bomb.h"

Psydb3Engine::Psydb3Engine() 
	: m_noOfDisplayObjects(3) {
	//initialise state here
	//m_gameState = new Psydb3PlayState;
}

Psydb3Engine::~Psydb3Engine() {
}

void Psydb3Engine::SetupBackgroundBuffer() {

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
	char* data[] = { //for testing tank motion
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

	m_oTiles.SetSize(28, 18);

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 18; ++j)
			m_oTiles.SetValue(i, j, data[j][i] - 'a');
	}
	m_oTiles.SetBaseTilesPositionOnScreen(0, 0);

	m_oTiles.DrawAllTiles(this,
		this->GetBackground(),
		0, 0, 27, 17);
}

int Psydb3Engine::InitialiseObjects() {
	DrawableObjectsChanged();

	DestroyOldObjects();

	CreateObjectArray(m_noOfDisplayObjects + 1);
	StoreObjectInArray(0, new Psydb3Bomb(this, GetTime(), 500, 500));
	StoreObjectInArray(1, new Psydb3PlayerTank(this, 500.0, 500.0));
	StoreObjectInArray(2, new Psydb3Cursor(this));
	StoreObjectInArray(m_noOfDisplayObjects, NULL);

	return 0;
}

void Psydb3Engine::GameAction() {
	if (!IsTimeToAct())
		return;

	SetTimeToAct(5);

	UpdateAllObjects(GetModifiedTime());
}