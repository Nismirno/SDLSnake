#pragma once
#ifndef _ENTITY_H
#define _ENTITY_H

#include <SDL.h>

#include "Globals.h"

// Simple entity base class
class Entity {
public:
	Entity();
	Entity(int x, int y, bool isFood = false);
	~Entity();

	inline SDL_Rect getCollider() const {
		return m_collider;
	}
	inline Loc getPosition() const {
		return m_position;
	}
	bool isFood() const {
		return m_isFood;
	}

protected:
	Loc m_position;

	SDL_Rect m_collider;

	bool m_isFood;
};

#endif // !_ENTITY_H


