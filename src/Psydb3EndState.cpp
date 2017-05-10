#include "Psydb3EndState.h"


Psydb3EndState::Psydb3EndState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine) {
}


Psydb3EndState::~Psydb3EndState() {
}

void Psydb3EndState::HandleKeys(int iKeyCode) {
	switch (iKeyCode) {
		case SDLK_SPACE:
			m_pEngine->SetState(START_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(false);
			break;
	}
}

void Psydb3EndState::DrawOntop() {
	m_pEngine->DrawScreenString(550, 250, "MISSION FAILED", 0x990000, m_pEngine->GetFont("Blockletter.otf", 110));
	m_pEngine->DrawScreenString(500, 450, "press space to return to main menu", 0x990000, m_pEngine->GetFont("Blockletter.otf", 50));
}