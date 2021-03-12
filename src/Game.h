//
// Created by Vilhelm Stokstad on 2021-02-17.
//

#pragma once

#include "include.h"
#include "Player.h"
#include "Asteroid.h"





class Game
{
public:

	Game()
	= default;


	int Init();

	Player* player{};

	bool appRunning = true;

	int GameLoop();

	int StartGame();

	int HandleEvents();

	int Render(double alpha) const;

	int Update(time_point dt);

	int Cleanup() const;

	Asteroid* asteroid{};
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event events = SDL_Event();

};


