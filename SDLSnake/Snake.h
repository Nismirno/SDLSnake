#pragma once
#ifndef _SNAKE_H
#define _SNAKE_H

#include "Texture.h"
#include "Globals.h"
#include "Timer.h"
#include "SnakePart.h"

class Snake {
public:
	// Initialize snake
	Snake();

	// Deallocate memory
	~Snake();

	// Handle key presses
	void handleEvent(const SDL_Event &e);

	// Load texture
	void loadHeadTexture(std::string path, SDL_Renderer *renderer);
	void loadBodyTexture(std::string path, SDL_Renderer *renderer);

	// Render snake
	void render(SDL_Renderer *renderer) const;

	// Move snake
	void move();

	// Spawn head
	void spawn(int x, int y);

	// Snake's growth
	void growth();

	// Get entities
	std::vector<SnakePart *> &getEntities();

private:
	// Snake textures
	Texture m_headTexture;
	Texture m_bodyTexture;

	// Snake parts
	std::vector<SnakePart *> m_parts;

	// Movement timer
	Timer m_timer;

	// Size of snake
	int m_size;

};

#endif // !_SNAKE_H

