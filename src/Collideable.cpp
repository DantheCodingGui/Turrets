#include "Collideable.h"


Collideable::Collideable(Psydb3CollisionHandler* collisionHandler) 
	: m_collisionHandler(collisionHandler)
	, m_collidingX(false)
	, m_collidingY(false)
	, m_behindTile(false) {
}


Collideable::~Collideable() {
}
