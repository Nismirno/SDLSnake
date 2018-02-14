#include "Food.h"



Food::Food() :
	m_posX(0),
	m_posY(0),
	m_width(0),
	m_height(0),
	m_isSpawned(false) {}


Food::~Food() {}


void Food::loadTexture(std::string path, SDL_Renderer *renderer) {
	m_texture.loadFromFile(path, renderer);
	m_height = m_texture.getHeight();
	m_width = m_texture.getWidth();
	initColliders();
}


void Food::spawn() {
	if (!m_isSpawned) {
		std::random_device rd;
		std::uniform_int_distribution<int> dist(0, MAP_SIZE - 1);
		m_posX = dist(rd) * m_width;
		m_posY = dist(rd) * m_height;
		m_isSpawned = true;
		shiftColliders();
	}
}


void Food::despawn() {
	m_isSpawned = false;
}


bool Food::isSpawned() const {
	return m_isSpawned;
}


void Food::render(SDL_Renderer *renderer) {
	m_texture.render(renderer, m_posX, m_posY);
}


const SDL_Rect &Food::getColliders() const {
	return m_collider;
}


void Food::initColliders() {
	m_collider.h = m_height;
	m_collider.w = m_width;
	shiftColliders();
}

void Food::shiftColliders() {
	m_collider.x = m_posX;
	m_collider.y = m_posY;
}
