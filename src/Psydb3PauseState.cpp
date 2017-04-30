#include "Psydb3PauseState.h"


Psydb3PauseState::Psydb3PauseState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine) {
}


Psydb3PauseState::~Psydb3PauseState() {
}

void Psydb3PauseState::SetupBackgroundBuffer() {

}

void Psydb3PauseState::Update() {
}

void Psydb3PauseState::HandleKeys(int iKeyCode) {
	
	switch (iKeyCode) {
		case SDLK_p: 
			m_pEngine->SetState(PLAY_STATE);
			break;
	}
}