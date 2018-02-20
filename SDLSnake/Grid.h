#pragma once
#ifndef _GRID_H
#define _GRID_H
#include <SDL.h>

#include <vector>
#include <random>
#include <cmath>

#include "Globals.h"
#include "Snake.h"
#include "Food.h"
#include "Entity.h"
#include "Timer.h"

struct Cell {
	int x;
	int y;
	int w;
	int h;
	bool isEmpty;
	std::vector<Entity *> entities;
};

typedef std::vector<std::vector<Cell>> Cells;

class Grid {
public:
	// Initialize variable
	Grid();

	// Deallocate memory
	~Grid();

	void handleEvent(const SDL_Event &e);

	void create(SDL_Renderer *renderer);

	bool updateGrid();

	void updateCells();
	void clearCells();

	bool processCollisions();

	void pushEntity(Entity *entity);

	void render(SDL_Renderer *renderer);

	Loc spawnLocation();

	Loc getCellPos(int i, int j) const;

	int getSize() const;

	bool isCellEmpty(int i, int j) const;

private:
	Snake *m_snake;
	Food *m_food;
	Cells m_cells;

	Timer m_timer;

	std::vector<Entity *> m_entities;

	int m_cellSize;

	int m_gridSize;

	bool m_gameOver;
};

#endif // !_GRID_H

