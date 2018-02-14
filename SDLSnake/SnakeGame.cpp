#include "SnakeGame.h"


SnakeGame::SnakeGame() {}

SnakeGame::~SnakeGame() {
	m_gameWindow.free();
}

bool SnakeGame::init() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags)) & imgFlags) {
		printf("SDL_image could not initialize! SDL Error: %s\n", IMG_GetError());
		return false;
	}

	// Set texture filtering
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!\n");
		return false;
	}

	if (!m_gameWindow.init()) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	m_gameWindow.createRenderer();

	if (m_gameWindow.renderer() == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}


bool SnakeGame::execute() {
	bool quit = false;
	SDL_Event e;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			uint32_t eventType = e.type;
			SDL_Keycode keyCode = e.key.keysym.sym;

			// Exit the game
			if (eventType == SDL_QUIT) {
				quit = true;
			}

			if (eventType == SDL_WINDOWEVENT_RESIZED) {
				resize(e.window.data1, e.window.data2);
			}
		}

		update();
		SDL_RenderPresent(m_gameWindow.renderer());
	}

	return true;
}


bool SnakeGame::finalize() {
	m_gameWindow.free();
	return true;
}


void SnakeGame::update() {
	SDL_SetRenderDrawColor(m_gameWindow.renderer(), 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(m_gameWindow.renderer());
}


void SnakeGame::resize(int width, int height) {
	return;
}
