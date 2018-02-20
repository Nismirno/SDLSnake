#include "Food.h"



Food::Food() : Entity(0, 0, true) {}

Food::~Food() {}


void Food::loadTexture(std::string path, SDL_Renderer *renderer) {
	m_texture.loadFromFile(path, renderer);
}


void Food::spawn(Loc spawnLoc) {
	if (!m_isSpawned) {
		m_position.x = spawnLoc.x;
		m_position.y = spawnLoc.y;
		m_isSpawned = true;
		shiftCollider();
	}
}


void Food::despawn() {
	m_isSpawned = false;
}


bool Food::isSpawned() const {
	return m_isSpawned;
}


void Food::render(SDL_Renderer *renderer) {
	m_texture.setDimensions(TEXTURE_SIZE, TEXTURE_SIZE);
	m_texture.render(renderer, m_position.x, m_position.y);
}
