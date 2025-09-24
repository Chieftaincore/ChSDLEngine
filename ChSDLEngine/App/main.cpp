#include <iostream>
#include <SDL.h>
#include "../Engine/Game.h"

int main(int argc, char* argv[]) {

	Game game;

	if (game.Init("chieftaincore's SDL Engine", 1280, 960) == false)
		return -1;
	
	game.Run();
	return 0;
}

