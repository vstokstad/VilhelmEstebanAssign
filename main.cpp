#include "Game.h"
#include "TextureManager.h"

class Game;

int main(int argc, char** argv)
{



	Game game = Game();

	game.StartGame();

	game.Cleanup();


	return 0;
}

