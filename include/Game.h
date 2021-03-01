//
// Created by Vilhelm Stokstad on 2021-02-17.
//




#include "include.h"
#include "Player.h"

class Game
{
public:

	Game();

	void Init();

	Player* player;

	bool appRunning = true;

	void GameLoop();

	void HandleEvents();

	void Render();

	void Update();

	void Cleanup() const;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event events{};
	Vector2Int* screenSize = nullptr;

};


