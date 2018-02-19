#include "Entity.h"


Entity::Entity() {
	m_position = { 0, 0 };
	m_isFood = false;
}


Entity::Entity(int x, int y, bool isFood) {
	m_position = { x, y };
	m_isFood = isFood;
}


Entity::~Entity() {}
