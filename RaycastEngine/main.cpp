#include <iostream>

#include "Game.hpp"

int main(int argc, char* argv[]) {
	WindowInfo wInfo("Raycast Engine", 800, 600);
	ContextInfo cInfo;
	Game game(wInfo, cInfo);
	game.run();
	return 0;
}