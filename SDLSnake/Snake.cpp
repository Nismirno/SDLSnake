#include "Snake.h"


const int Snake::s_step = 64;
int Snake::s_size = 1;

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
}


void Snake::loadTexture(std::string path, SDL_Renderer *renderer) {
	m_texture.loadFromFile(path, renderer);
	m_height = m_texture.getHeight();
	m_width = m_texture.getWidth();
	initColliders();
}


void Snake::render(SDL_Renderer *renderer) const {
	m_texture.render(renderer, m_posX, m_posY);
}


void Snake::move(Food &food) {
	// Start timer if it is stopped
	if (!m_timer.isStarted()) {
		m_timer.start();
	}

	// Wait one second to move
	if (m_timer.getTicks() < 1000) {
		return;
	}

	// Reset timer
	m_timer.stop();

	// If part is head
	if (m_isHead) {
		// Move horizontally
		m_posX += m_velX * s_step;
		shiftColliders();

		// If reached wall
		if (m_posX < 0 || m_posX + m_width > SCREEN_WIDTH) {
			m_posX -= m_velX * s_step;
			shiftColliders();
			m_velX = 0;
		}

		// Move vertically
		m_posY += m_velY * s_step;
		shiftColliders();

		// If reached wall
		if (m_posY < 0 || m_posY + m_height > SCREEN_HEIGHT) {
			m_posY -= m_velY * s_step;
			shiftColliders();
			m_velY = 0;
		}

		if (checkCollision(food)) {
			food.despawn();
		}
	}

	/*
	TODO: Implement body movement
	*/
	// Restart timer
	m_timer.start();
}


void Snake::growth() {
	/*
	TODO: Implement snake growth
	*/
}


bool Snake::checkCollision(const Snake &body) const {
	return false;
}


bool Snake::checkCollision(const Food &food) const {
	const SDL_Rect &a = m_collider;
	const SDL_Rect &b = food.getColliders();
	// The sides of rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	// Calculate the sides of rectA
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	// Calculate the sides of rectB
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	// If any of the sides of A are outside of B
	if (bottomA <= topB || bottomB <= topA ||
	    rightA <= leftB || rightB <= leftA) {
		return false;
	}

	return true;
}


const SDL_Rect &Snake::getColliders() const {
	return m_collider;
}


void Snake::initColliders() {
	m_collider.h = m_height;
	m_collider.w = m_width;
	shiftColliders();
}

void Snake::shiftColliders() {
	m_collider.x = m_posX;
	m_collider.y = m_posY;
}

