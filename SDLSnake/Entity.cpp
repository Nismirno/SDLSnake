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


void Entity::shiftCollider() {
	m_collider.h = TEXTURE_SIZE;
	m_collider.w = TEXTURE_SIZE;
	m_collider.x = m_position.x;
	m_collider.y = m_position.y;
}
