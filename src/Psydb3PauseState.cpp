#include "Psydb3PauseState.h"


Psydb3PauseState::Psydb3PauseState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine) {
}


Psydb3PauseState::~Psydb3PauseState() {
}

void Psydb3PauseState::DrawBackground() {
	m_pEngine->FillBackground(0xffffff);
	m_pEngine->DrawBackgroundString(100, 100, "Game Paused", 0x332100, m_pEngine->GetFont("Blockletter.otf", 100));
}

void Psydb3PauseState::Update() {
}

void Psydb3PauseState::HandleKeys(int iKeyCode) {
	
	switch (iKeyCode) {
		case SDLK_ESCAPE:
			m_pEngine->SetState(START_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(false);
			SDL_ShowCursor(SDL_ENABLE); //disable the mouse icon while playing
			break;
		case SDLK_SPACE: 
			m_pEngine->SetState(PLAY_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(true);
			break;
	}
}