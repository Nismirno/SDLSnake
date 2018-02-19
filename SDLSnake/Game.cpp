#include "Game.h"
#include <Windows.h>

Game::Game() {}


Game::~Game() {
	m_gameWindow.free();
}


bool Game::init() {
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


bool Game::execute() {
	SDL_Renderer *renderer = m_gameWindow.renderer();
	bool quit = false;
	SDL_Event e;
	Snake *snake = new Snake();
	snake->loadHeadTexture("media/body.png", renderer);
	snake->loadBodyTexture("media/body.png", renderer);
	snake->spawn(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Food food;
	food.loadTexture("media/food.png", renderer);

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			uint32_t eventType = e.type;
			SDL_Keycode keyCode = e.key.keysym.sym;

			// Exit the game
			if (eventType == SDL_QUIT) {
				quit = true;
			}

			m_gameWindow.handleEvent(e);
			snake->handleEvent(e);
		}

		snake->move();
		clearScreen();
		snake->render(renderer);
		//		food.render(renderer);
		SDL_RenderPresent(renderer);
	}

	return true;
}


bool Game::finalize() {
	m_gameWindow.free();
	return true;
}


void Game::clearScreen() {
	SDL_Renderer *renderer = m_gameWindow.renderer();
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}


void Game::resize(int width, int height) {
	return;
}
