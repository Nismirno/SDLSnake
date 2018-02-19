#include "Snake.h"


Snake::Snake() {
	m_size = 0;
}


Snake::~Snake() {}


void Snake::handleEvent(const SDL_Event &e) {
	m_parts[0]->handleEvent(e);
}


void Snake::loadHeadTexture(std::string path, SDL_Renderer *renderer) {
	m_headTexture.loadFromFile(path, renderer);
	m_headTexture.setDimensions(TEXTURE_SIZE, TEXTURE_SIZE);
}


void Snake::loadBodyTexture(std::string path, SDL_Renderer *renderer) {
	m_bodyTexture.loadFromFile(path, renderer);
	m_bodyTexture.setDimensions(TEXTURE_SIZE, TEXTURE_SIZE);
}


void Snake::render(SDL_Renderer *renderer) const {
	for (SnakePart const *part : m_parts) {
		if (part->isHead()) {
			part->render(m_headTexture, renderer);
		} else {
			part->render(m_bodyTexture, renderer);
		}
	}
}


void Snake::move() {
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
	Loc prevPosition = { 0, 0 };

	for (SnakePart *part : m_parts) {
		part->move(prevPosition);
		prevPosition = part->getPrevPosition();
	}

	// Restart timer
	m_timer.start();
}


void Snake::spawn(int x, int y) {
	if (m_size != 0) {
		printf("Snake size is not 0! Nothing to spawn.\n");
		return;
	}

	SnakePart *newPart = new SnakePart(x, y, true);
	m_parts.push_back(newPart);
	m_size++;
}


void Snake::growth() {
	if (m_size == 0) {
		printf("No head! Nothing to grow\n");
		return;
	}

	SnakePart *prevPart = m_parts.back();
	Loc prevLoc = prevPart->getPrevPosition();
	SnakePart *newPart = new SnakePart(prevLoc.x, prevLoc.y);
	m_parts.push_back(newPart);
	m_size++;
}


std::vector<SnakePart *> &Snake::getEntities() {
	return m_parts;
}
