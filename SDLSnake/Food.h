#pragma once
#ifndef _FOOD_H
#define _FOOD_H
#include <SDL.h>

#include <random>

#include "Texture.h"
#include "Globals.h"

class Food {
public:
	// Initialize members
	Food();

	// Deallocate memory
	~Food();

	// Load texture
	void loadTexture(std::string path, SDL_Renderer *renderer);

	// Spawn food
	void spawn();

	// Despawn food
	void despawn();

	// Is food spawned
	bool isSpawned() const;

	// Render texture
	void render(SDL_Renderer *renderer);

	// Get colliders
	const SDL_Rect &getColliders() const;

private:
	// Food texture
	Texture m_texture;

	// Position of food
	int m_posX, m_posY;

	// Dimensions
	int m_width, m_height;

	// Spawn flag
	bool m_isSpawned;

	// Collision box
	SDL_Rect m_collider;

	// Initialize collider
	void initColliders();

	// Shift collider
	void shiftColliders();
};

#endif // !_FOOD_H
