#include "Psydb3Engine.h"
#include "header.h"

#include "Psydb3PlayerTank.h"
#include "Psydb3Cursor.h"
#include "Psydb3Bomb.h"

#include "Psydb3StartState.h"
#include "Psydb3PlayState.h"
#include "Psydb3PauseState.h"

#define START_STATE		0
#define PLAY_STATE		1
#define PAUSE_STATE		2
#define END_WIN_STATE	3
#define END_LOSE_STATE	4

Psydb3Engine::Psydb3Engine() 
	: m_noOfDisplayObjects(3) {
	InitialiseGameStates();
	SetState(PLAY_STATE);
}

Psydb3Engine::~Psydb3Engine() {
	for (int i = 0; i < 5; ++i)
		delete m_gameStates[i];
}

void Psydb3Engine::SetupBackgroundBuffer() {

	m_activeGameState->SetupBackgroundBuffer();
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

void Psydb3Engine::InitialiseGameStates() {
	m_gameStates[0] = new Psydb3StartState(this);
	m_gameStates[1] = new Psydb3PlayState(this); 
	m_gameStates[2] = new Psydb3PauseState(this);
}

void Psydb3Engine::GameAction() {
	if (!IsTimeToAct())
		return;

	SetTimeToAct(5);

	if (m_activeGameState->ShouldAct())
		UpdateAllObjects(GetModifiedTime());
}