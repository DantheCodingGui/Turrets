#include "Psydb3StartState.h"


Psydb3StartState::Psydb3StartState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine){
}


Psydb3StartState::~Psydb3StartState() {
}

void Psydb3StartState::SetupBackgroundBuffer() {
	m_pEngine->FillBackground(0xffffff);
}

void Psydb3StartState::Update() {

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