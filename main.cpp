#include "Game.h"
#include "include.h"
class Game;

const auto screenSize = Vector2Int(1200, 800);
int main(int argc, char** argv)
{

	SDL_Init(SDL_INIT_EVERYTHING);

	Game game = Game();
	game.Init();

	game.GameLoop();

	game.Cleanup();

	SDL_Quit();


	return 0;
}

