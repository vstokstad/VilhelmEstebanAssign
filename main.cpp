#include "Game.h"
#include "include.h"
int main(int argc, char** argv)
{

	SDL_Init(SDL_INIT_EVERYTHING);

	Game game = Game();
	game.Init();

	game.GameLoop();

	if (!game.Cleanup()){

	SDL_Quit();
	};

	return 0;
}

