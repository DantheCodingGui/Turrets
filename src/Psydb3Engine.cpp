#include "Psydb3Engine.h"
#include "header.h"

#include "Psydb3StartState.h"
#include "Psydb3PlayState.h"
#include "Psydb3PauseState.h"

#define START_STATE		0
#define PLAY_STATE		1
#define PAUSE_STATE		2
#define END_WIN_STATE	3
#define END_LOSE_STATE	4

Psydb3Engine::Psydb3Engine()  {
	InitialiseGameStates();
	SetState(START_STATE);
}

Psydb3Engine::~Psydb3Engine() {
	for (int i = 0; i < 3; ++i)
		delete m_gameStates[i];
}

void Psydb3Engine::SetupBackgroundBuffer() {

	m_activeGameState->DrawBackground();
}

int Psydb3Engine::InitialiseObjects() {
	DrawableObjectsChanged();

	DestroyOldObjects();

	//since this only ever applies to playstate
	dynamic_cast<Psydb3PlayState*>(m_gameStates[PLAY_STATE])->InitialiseObjects();

	return 0;
}

void Psydb3Engine::InitialiseGameStates() {
	m_gameStates[START_STATE] = new Psydb3StartState(this);
	m_gameStates[PLAY_STATE] = new Psydb3PlayState(this);
	m_gameStates[PAUSE_STATE] = new Psydb3PauseState(this);
}

void Psydb3Engine::GameAction() {
	if (!IsTimeToAct())
		return;

	SetTimeToAct(10);

	m_activeGameState->Update();
}

void Psydb3Engine::KeyUp(int iKeyCode)
{
	m_activeGameState->HandleKeys(iKeyCode);
}

void Psydb3Engine::MouseUp(int iButton, int iX, int iY) {
	m_activeGameState->HandleMouse();
}

void Psydb3Engine::DrawStringsOnTop() {
	m_activeGameState->DrawOntop();
}

void Psydb3Engine::UnDrawStrings() {
	m_activeGameState->UnDrawStrings();
}