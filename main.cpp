#include "Game.h"

int main(int argc, char** argv)
{

	Game game = Game();
	game.Init();



	game.GameLoop();



	game.Cleanup();


	return 0;
}

