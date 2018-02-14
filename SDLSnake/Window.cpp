#include "Window.h"



Window::Window() {
	m_window = NULL;
	m_renderer = NULL;
	m_mouseFocus = false;
	m_keyboardFocus = false;
	m_isMinimized = false;
	m_isFullscreen = false;
	m_width = 0;
	m_height = 0;
}


Window::~Window() {
	free();
}


bool Window::init() {
	m_window = SDL_CreateWindow("Snake",
															SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
															SCREEN_WIDTH, SCREEN_HEIGHT,
															SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (m_window != NULL) {
		m_mouseFocus = true;
		m_keyboardFocus = true;
		m_width = SCREEN_WIDTH;
		m_height = SCREEN_HEIGHT;
	}

	return m_window != NULL;
}


void Window::createRenderer() {
	uint32_t renderFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	m_renderer = SDL_CreateRenderer(m_window, -1, renderFlags);
}


void Window::handleEvent(SDL_Event &e) {
	if (e.type == SDL_WINDOWEVENT) {
		bool updateCaption = false;

		switch (e.window.event) {
		// Get new dimensions and repaint on window size change
		case SDL_WINDOWEVENT_SIZE_CHANGED:
				m_width = e.window.data1;
				m_height = e.window.data2;
				SDL_RenderPresent(m_renderer);
				break;

		// Repaint on exposure 
		case  SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(m_renderer);
			break;
		
		// Mouse entered window 
		case SDL_WINDOWEVENT_ENTER:
			m_mouseFocus = true;
			break;

		// Mouse left window
		case SDL_WINDOWEVENT_LEAVE:
			m_mouseFocus = false;
			break;

		// Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			m_keyboardFocus = true;
			break;

		// Window has keyboard focus
		case SDL_WINDOWEVENT_FOCUS_LOST:
			m_keyboardFocus = false;
			break;
			
		// Window minimized
		case SDL_WINDOWEVENT_MINIMIZED:
			m_isMinimized = true;
			break;

		// Window maximized
		case SDL_WINDOWEVENT_MAXIMIZED:
			m_isMinimized = false;
			break;

		// Window restored
		case SDL_WINDOWEVENT_RESTORED:
			m_isMinimized = false;
			break;
		}
	} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
		if (m_isFullscreen) {
			SDL_SetWindowFullscreen(m_window, SDL_FALSE);
			m_isFullscreen = false;
		} else {
			SDL_SetWindowFullscreen(m_window, SDL_TRUE);
			m_isFullscreen = true;
			m_isMinimized = false;
		}
	}
}


void Window::free() {
	if (m_window != NULL) {
		SDL_DestroyWindow(m_window);
	}

	if (m_renderer != NULL) {
		SDL_DestroyRenderer(m_renderer);
	}

	m_mouseFocus = false;
	m_keyboardFocus = false;
	m_width = 0;
	m_height = 0;
}


int Window::getHeight() const {
	return m_height;
}


int Window::getWidth() const {
	return m_width;
}


bool Window::hasMouseFocus() const {
	return m_mouseFocus;
}


bool Window::hasKeyboardFocus() const {
	return m_keyboardFocus;
}


bool Window::isMinimized() const {
	return m_isMinimized;
}


SDL_Renderer* Window::renderer(){
	return m_renderer;
}
