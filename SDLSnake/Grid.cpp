#include "Grid.h"


Grid::Grid() {
	m_gridSize = MAP_SIZE;
	m_cellSize = TEXTURE_SIZE;
	m_cells.resize(m_gridSize);

	for (int i = 0; i < m_gridSize; i++) {
		m_cells[i].resize(m_gridSize);

		for (int j = 0; j < m_gridSize; j++) {
			m_cells[i][j].h = m_cellSize;
			m_cells[i][j].w = m_cellSize;
			m_cells[i][j].x = m_cellSize * i;
			m_cells[i][j].y = m_cellSize * j;
			m_cells[i][j].isEmpty = true;
		}
	}

	m_snake = new Snake();
	m_food = new Food();
	m_gameOver = false;
}


Grid::~Grid() {}


void Grid::handleEvent(const SDL_Event &e) {
	m_snake->handleEvent(e);
	//	printf("Event handled.\n");
}


void Grid::create(SDL_Renderer *renderer) {
	m_snake->loadBodyTexture("media/body.png", renderer);
	m_snake->loadHeadTexture("media/head.png", renderer);
	m_snake->spawn(spawnLocation());
	m_food->loadTexture("media/food.png", renderer);
	m_food->spawn(spawnLocation());
	std::vector<SnakePart *> parts = m_snake->getEntities();
	pushEntity(m_food);
	pushEntity(parts.back());
}


bool Grid::updateGrid() {
	if (!m_timer.isStarted()) {
		m_timer.start();
	}

	if (!m_food->isSpawned()) {
		m_food->spawn(spawnLocation());
	}

	if (m_timer.getTicks() < 250) {
		return false;
	}

	m_timer.stop();

	if (m_snake->move()) {
		return true;
	}

	updateCells();
	bool isFoodEaten = processCollisions();

	if (m_gameOver) {
		printf("Game over\n");
		return true;
	}

	if (isFoodEaten) {
		m_food->despawn();
		m_snake->growth();
		std::vector<SnakePart *> parts = m_snake->getEntities();
		pushEntity(parts.back());
	}

	m_timer.start();
	return false;
}


void Grid::updateCells() {
	int i, j;
	clearCells();

	for (auto *entity : m_entities) {
		Loc entityPos = entity->getPosition();
		i = static_cast<int>(std::floor(entityPos.x / m_cellSize));
		j = static_cast<int>(std::floor(entityPos.y / m_cellSize));
		m_cells[i][j].entities.push_back(entity);
		m_cells[i][j].isEmpty = false;
	}
}


void Grid::clearCells() {
	for (auto &column : m_cells) {
		for (auto &cell : column) {
			cell.entities.clear();
			cell.isEmpty = true;
		}
	}
}


bool Grid::processCollisions() {
	for (auto &column : m_cells) {
		for (auto &cell : column) {
			if (cell.isEmpty || cell.entities.size() < 2) continue;

			for (size_t i = 0; i < cell.entities.size(); i++) {
				auto entityA = cell.entities[i];

				for (size_t j = i + 1; j < cell.entities.size(); j++) {
					auto entityB = cell.entities[j];
					auto snakeEntityA = dynamic_cast<SnakePart *>(entityA);
					auto snakeEntityB = dynamic_cast<SnakePart *>(entityB);

					if (!entityA->isFood() && !entityB->isFood()) {
						m_gameOver = true;
						printf("Collided with tail.\n");
						return false;
					}

					if (entityA->isFood() || entityB->isFood()) {
						return true;
					}
				}
			}
		}
	}

	return false;
}


void Grid::pushEntity(Entity *entity) {
	m_entities.push_back(entity);
}


void Grid::render(SDL_Renderer *renderer) {
	m_food->render(renderer);
	m_snake->render(renderer);
}


Loc Grid::spawnLocation() {
	bool isEmptyCell = false;
	int cellCol, cellRow;

	do {
		std::random_device rd;
		std::uniform_int_distribution<int> dist(0, MAP_SIZE - 1);
		cellCol = dist(rd);
		cellRow = dist(rd);
		isEmptyCell = isCellEmpty(cellCol, cellRow);
	} while (!isEmptyCell);

	m_cells[cellCol][cellRow].isEmpty = false;
	return getCellPos(cellCol, cellRow);
}


Loc Grid::getCellPos(int i, int j) const {
	Loc cellPos;
	cellPos.x = m_cells[i][j].x;
	cellPos.y = m_cells[i][j].y;
	return cellPos;
}


int Grid::getSize() const {
	return m_gridSize;
}


bool Grid::isCellEmpty(int i, int j) const {
	return m_cells[i][j].isEmpty;
}
