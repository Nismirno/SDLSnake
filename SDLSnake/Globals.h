#pragma once
#ifndef _GLOBALS_H
#define _GLOBALS_H

// Constants
extern constexpr int SCREEN_WIDTH = 640;
extern constexpr int SCREEN_HEIGHT = 640;

extern constexpr int MAP_SIZE = 20;

extern constexpr int TEXTURE_SIZE = 32;

// Structs

struct Loc {
	int x;
	int y;
};

#endif // !_GLOBALS_H
