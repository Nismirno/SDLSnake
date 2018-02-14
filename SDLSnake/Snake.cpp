#include "Snake.h"


const int Snake::s_step = 64;

Snake::Snake() :
	m_posX(0),
	m_posY(0),
	m_velX(0),
	m_velY(0),
	m_width(0),
	m_height(0),
	m_velocityMultiplier(1),
	m_isHead(true),
	m_nextPart(nullptr),
	m_previousPart(nullptr) {}


Snake::Snake(int x, int y) :
	m_posX(x),
	m_posY(y),
	m_velX(0),
	m_velY(0),
	m_width(0),
	m_height(0),
	m_velocityMultiplier(1),
	m_isHead(true),
	m_nextPart(nullptr),
	m_previousPart(nullptr) {}


Snake::~Snake() {
	delete m_nextPart;
	delete m_previousPart;
}


void Snake::handleEvent(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN && m_isHead) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			m_velY = -1 * m_velocityMultiplier;
			m_velX = 0;
			break;

		case SDLK_DOWN:
			m_velY = 1 * m_velocityMultiplier;
			m_velX = 0;
			break;

		case SDLK_LEFT:
			m_velX = -1 * m_velocityMultiplier;
			m_velY = 0;
			break;

		case SDLK_RIGHT:
			m_velX = 1 * m_velocityMultiplier;
			m_velY = 0;
			break;

		default:
			break;
		}
	}

	printf("Snake speed x: %i; y: %i\n", m_velX, m_velY);
}


void Snake::loadTexture(std::string path, SDL_Renderer *renderer) {
	m_texture.loadFromFile(path, renderer);
	m_height = m_texture.getHeight();
	m_width = m_texture.getWidth();
}


void Snake::render(SDL_Renderer *renderer) const {
	m_texture.render(renderer, m_posX, m_posY);
}


void Snake::move() {
	// If part is head
	if (m_isHead) {
		// Move horizontally
		m_posX += m_velX * s_step;

		// If reached wall
		if (m_posX < 0 || m_posX + m_width > SCREEN_WIDTH) {
			m_posX -= m_velX * s_step;
			m_velX = 0;
		}

		// Move vertically
		m_posY += m_velY * s_step;

		// If reached wall
		if (m_posY < 0 || m_posY + m_height > SCREEN_HEIGHT) {
			m_posY -= m_velY * s_step;
			m_velY = 0;
		}
	}
}
