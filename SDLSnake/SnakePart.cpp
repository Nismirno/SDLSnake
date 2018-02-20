#include "SnakePart.h"


const int SnakePart::m_stepSize = TEXTURE_SIZE;

SnakePart::SnakePart() : Entity() {}


SnakePart::SnakePart(int x, int y, bool isHead, bool isFood) :
	Entity(x, y, isFood) {
	m_prevPosition = { 0, 0 };
	m_velocity = { 0, 0 };
	m_isHead = isHead;
}


SnakePart::~SnakePart() {}


void SnakePart::handleEvent(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN && m_isHead) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			m_velocity.y = -1;
			m_velocity.x = 0;
			break;

		case SDLK_DOWN:
			m_velocity.y = 1;
			m_velocity.x = 0;
			break;

		case SDLK_LEFT:
			m_velocity.y = 0;
			m_velocity.x = -1;
			break;

		case SDLK_RIGHT:
			m_velocity.y = 0;
			m_velocity.x = 1;
			break;

		default:
			break;
		}
	}
}


void SnakePart::render(const Texture &texture, SDL_Renderer *renderer) const {
	texture.render(renderer, m_position.x, m_position.y);
}


bool SnakePart::move(Loc location) {
	bool gameOver = false;

	if (m_isHead) {
		// Safe previous position
		m_prevPosition = m_position;
		m_position.x += m_velocity.x * m_stepSize;
		shiftCollider();

		if (m_position.x < 0 || m_position.x + m_collider.w > SCREEN_WIDTH) {
			gameOver = true;
		}

		m_position.y += m_velocity.y * m_stepSize;
		shiftCollider();

		if (m_position.y < 0 || m_position.y + m_collider.h > SCREEN_HEIGHT) {
			gameOver = true;
		}

		return gameOver;
	} else {
		m_prevPosition = m_position;
		m_position = location;
		shiftCollider();
	}

	return gameOver;
}
