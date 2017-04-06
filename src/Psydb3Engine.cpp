#include "Psydb3Engine.h"
#include "header.h"

Psydb3Engine::Psydb3Engine() {
}


Psydb3Engine::~Psydb3Engine() {
}

void Psydb3Engine::SetupBackgroundBuffer() {

	char* data[] = {
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaaaaaaaaaaaaaaa",
		"abbbbbbccbbbbbbbbcbbbbbbbbca",
		"abaaaaaaaaaaaaaaaaaaaaaaaaba",
		"abaaaaaaaaaaaaaaaaaaaaaaaaba",
		"abaaaaaaaaaaaaaaaaaaaaaaaaba",
		"abaaaaaaaaaaaacbbaaaaaaaaaba",
		"abaaaaaaaaaaaaaabaaaaaaaaaba",
		"abaaaaaaaaaaaaaabaaaaaaaaaba",
		"abaaaaaabcdbbaaaaaaaaaaaaaba",
		"acaaaaaaaaaaaaaaaaaaabaaaaba",
		"abaaaaaaaaaaaaaaaaaaaaaaaaba",
		"abaaaaaaaaaaaadaaaaaaaaaaaba",
		"abaaaaaaaaaaaadaaaaaaaaaaaba",
		"abaaaaaaaaaadcdaaaaaaaaaaaba",
		"abaaaaaaaaaaaaaaaaaaaaaaaaba",
		"abaaaaaaaaaaaaaaaaaaaaaaaaba",
		"abbbbbccbbbbbbbbbbbbbbcccbba" };

	m_oTiles.SetSize(28, 18);

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 18; ++j)
			m_oTiles.SetValue(i, j, data[j][i] - 'a');
	}
	m_oTiles.SetBaseTilesPositionOnScreen(0, 0);

	m_oTiles.DrawAllTiles(this,
		this->GetBackground(),
		0, 0, 27, 17);
}