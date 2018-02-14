#pragma once
#ifndef _WINDOW_H
#define _WINDOW_H
#include <SDL.h>
#include "Globals.h"

class Window {
public:
	// Initialize members
	Window();

	// Deallocate memory
	~Window();

	// Create window
	bool init();

	// Create renderer from internal window
	void createRenderer();

	// Handles window events
	void handleEvent(SDL_Event &e);

	// Deallocate internals
	void free();

	// Get window dimensions
	int getWidth() const;
	int getHeight() const;

	// Window focus
	bool hasMouseFocus() const;
	bool hasKeyboardFocus() const;
	bool isMinimized() const;

	SDL_Renderer *renderer();

private:
	// Window data
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	// Window dimensions
	int m_width;
	int m_height;

	// Window focus
	bool m_mouseFocus;
	bool m_keyboardFocus;
	bool m_isFullscreen;
	bool m_isMinimized;
};

#endif // !_WINDOW_H

