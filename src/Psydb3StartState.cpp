#include "Psydb3StartState.h"
#include "JPGImage.h"


Psydb3StartState::Psydb3StartState(Psydb3Engine* pEngine)
	: Psydb3State(pEngine) {
}


Psydb3StartState::~Psydb3StartState() {
}

void Psydb3StartState::DrawBackground() {
	ImageData background;
	background.LoadImage("Backgrounds/Start_Background.png");
	background.FlexibleRenderImageWithMask(
		m_pEngine->GetBackground(), 
		0, 0, 0, 0,
		m_pEngine->GetScreenWidth(), m_pEngine->GetScreenHeight());
	m_pEngine->DrawBackgroundString(600, 600, "Press Space to Start", 0x000000, m_pEngine->GetFont("Blockletter.otf", 30));
	m_pEngine->DrawBackgroundString(50, 690, "Daniel Baxter 2017", 0x000000, m_pEngine->GetFont("Blockletter.otf", 20));
}

void Psydb3StartState::Update() {

}

void Psydb3StartState::HandleKeys(int iKeyCode) {
	
	switch (iKeyCode) {
		case SDLK_ESCAPE:
			m_pEngine->SetExitWithCode(0);
			break;
		case SDLK_SPACE:
			m_pEngine->SetState(PLAY_STATE);
			m_pEngine->SetupBackgroundBuffer();
			m_pEngine->Redraw(true);
			m_pEngine->SetAllVisibility(true);
			SDL_ShowCursor(SDL_DISABLE); //disable the mouse icon while playing
			break;
	}
}