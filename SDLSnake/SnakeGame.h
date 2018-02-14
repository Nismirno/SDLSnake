#pragma once
#ifndef _SNAKE_H
#define _SNAKE_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
//#include <SDL_opengl.h>
//#include <gl/GLU.h>

class SnakeGame {
public:
	// Initialize variables
	SnakeGame();

	// Deallocate memory
	~SnakeGame();

	// Window resolution
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 640;

	// Start up SDL and create window
	bool init();

	// Execute the game
	bool execute();

	// Finish the game
	bool finalize();

private:
	// Game window
	Window m_gameWindow;

	// Update screen
	void update();

	// Resize screen
	void resize(int width, int height);
};

#endif // !_SNAKE_H
