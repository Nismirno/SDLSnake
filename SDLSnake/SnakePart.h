#pragma once
#ifndef _SNAKEPART_H
#define _SNAKEPART_H
#include <SDL.h>

#include "Globals.h"
#include "Texture.h"
#include "Entity.h"

#include <string>

class SnakePart : public Entity {
public:
	// Initialize members
	SnakePart();
	SnakePart(int x, int y, bool isHead = false, bool isFood = false);

	// Deallocate memory
	~SnakePart();

	// Handle key presses
	void handleEvent(const SDL_Event &e);

	// Render part
	void render(const Texture &texture, SDL_Renderer *renderer) const;

	// Move part
	bool move(Loc location = { 0, 0 });

	inline bool isHead() const {
		return m_isHead;
	};

	inline Loc getPrevPosition() const {
		return m_prevPosition;
	}

	inline Loc getVelocity() const {
		return m_velocity;
	}


private:
	static const int m_stepSize;

	Loc m_prevPosition;
	Loc m_velocity;

	// Head flag
	bool m_isHead;
};

#endif // !_SNAKEPART_H
