#include "SnakeGame.h"



int main(int argv, char* argc[]) {
	SnakeGame game;

	if (!game.init()) {
		return 1;
	}

	if (!game.execute()) {
		return 1;
	}

	if (!game.finalize()) {
		return 1;
	}

	return 0;
}