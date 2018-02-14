#pragma once
#ifndef _SNAKE_H
#define _SNAKE_H
#include "Texture.h"
#include "Globals.h"

class Snake {
public:
	// Initialize snake
	Snake();
	Snake(int x, int y);

	// Deallocate memory
	~Snake();

	// Handle key presses
	void handleEvent(const SDL_Event &e);

	// Load texture
	void loadTexture(std::string path, SDL_Renderer *renderer);

	// Render snake
	void render(SDL_Renderer *renderer) const;

	// Move snake
	void move();

private:
	static const int s_step;
	// Snake texture
	Texture m_texture;

	// Connect the snake
	Snake *m_nextPart;
	Snake *m_previousPart;

	// Position of snake part
	int m_posX, m_posY;

	// Dimensions of the block
	int m_width, m_height;

	// Velocity of snake part
	int m_velX, m_velY;

	// Speed multiplier
	int m_velocityMultiplier;

	// Head flag
	bool m_isHead;
};

#endif // !_SNAKE_H

