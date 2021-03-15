#include "Game.h"

class Game;

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game = Game();

	game.StartGame();

	game.Cleanup();


	return 0;
}

