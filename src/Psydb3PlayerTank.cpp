#include "Psydb3PlayerTank.h"
#include "header.h"
#include "templates.h"


Psydb3PlayerTank::Psydb3PlayerTank(BaseEngine* pEngine)
	: Psydb3Tank(pEngine){
	anim1.LoadImage("Player_Tank_Horizontal_1.png");
}


Psydb3PlayerTank::~Psydb3PlayerTank()
{
}

void Psydb3PlayerTank::Draw() {
	anim1.RenderImageWithMask(this->GetEngine()->GetForeground(), 0, 0, 500, 500, anim1.GetWidth(), anim1.GetHeight());
}


