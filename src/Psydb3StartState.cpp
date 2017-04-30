#include "Psydb3StartState.h"


Psydb3StartState::Psydb3StartState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine){
}


Psydb3StartState::~Psydb3StartState() {
}

void Psydb3StartState::SetupBackgroundBuffer() {
	m_pEngine->FillBackground(0xffffff);
	m_pEngine->DrawBackgroundString(1200, 100, "Turrets", 0x332100, m_pEngine->GetFont("TOY SOLDIERS.ttf", 100));
	m_pEngine->DrawBackgroundString(500, 500, "Press Space to Start", 0x000000, m_pEngine->GetFont("TOY SOLDIERS.ttf", 50));
}

void Psydb3StartState::Update() {
	//m_pEngine->DrawScreenString(500, 500, "Press Space to Start", 0xffffff, m_pEngine->GetFont("TOY SOLDIERS.ttf", 50));
}

void Psydb3StartState::HandleKeys(int iKeyCode) {
	
	switch (iKeyCode) {
		case SDLK_SPACE:
			m_pEngine->SetState(PLAY_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(true);
			SDL_ShowCursor(SDL_DISABLE); //disable the mouse icon while playing
			break;
	}
}