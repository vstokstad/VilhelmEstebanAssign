//
// Created by Vilhelm Stokstad on 2021-02-17.
//

#pragma once

#include "include.h"
#include "Player.h"
#include "Asteroids.h"

class Game
{
public:

	Game()
	= default;

	int Init();

	Player* player = new Player();



	bool appRunning = true;

	int GameLoop();

	int StartGame();

	int HandleEvents();

	int Render() const;

	int Update() const;

	int Cleanup() const;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event events{};
	Vector2Int* screenSize = nullptr;

};


