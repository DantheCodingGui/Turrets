#include "Psydb3Engine.h"
#include "header.h"

#include "Psydb3PlayerTank.h"
#include "Psydb3Cursor.h"
#include "Psydb3Bomb.h"
#include "Psydb3PlayState.h"

Psydb3Engine::Psydb3Engine() 
	: m_noOfDisplayObjects(3) {
	//initialise state here
	m_gameState = new Psydb3PlayState(this);
}

Psydb3Engine::~Psydb3Engine() {
	delete m_gameState;
}

void Psydb3Engine::SetupBackgroundBuffer() {

	m_gameState->SetupBackgroundBuffer();
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