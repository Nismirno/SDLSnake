#pragma once
#ifndef _SNAKE_H
#define _SNAKE_H
#include "Texture.h"
#include "Globals.h"
#include "Timer.h"
#include "Food.h"

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
	void move(Food &food);

	// Snake's growth
	void growth();

	// Check collision
	bool checkCollision(const Snake &body) const;
	bool checkCollision(const Food &food) const;

	// Get colliders
	const SDL_Rect &getColliders() const;

private:
	// Step in pixels
	static const int s_step;

	// Size of snake
	static int s_size;

	// Snake texture
	Texture m_texture;

	// Movement timer
	Timer m_timer;

	// Connect the snake
	Snake *m_nextPart;
	Snake *m_previousPart;

	// Collision box
	SDL_Rect m_collider;

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

	// Initialize collider
	void initColliders();

	// Shift colliders
	void shiftColliders();
};

#endif // !_SNAKE_H

