#pragma once
#ifndef _FOOD_H
#define _FOOD_H
#include <SDL.h>

#include <random>

#include "Texture.h"
#include "Globals.h"
#include "Entity.h"

class Food : public Entity {
public:
	// Initialize members
	Food();

	// Deallocate memory
	~Food();

	// Load texture
	void loadTexture(std::string path, SDL_Renderer *renderer);

	// Spawn food
	void spawn(Loc spawnLoc);

	// Despawn food
	void despawn();

	// Is food spawned
	bool isSpawned() const;

	// Render texture
	void render(SDL_Renderer *renderer);

private:
	// Food texture
	Texture m_texture;

	// Spawn flag
	bool m_isSpawned;

};

#endif // !_FOOD_H
