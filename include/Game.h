//
// Created by Vilhelm Stokstad on 2021-02-17.
//



#pragma once
#include "include.h"
#include "Player.h"

class Game
{
public:

	Game()
	= default;

	int Init();

	Player* player;
	bool appRunning = true;

	int GameLoop();

	int HandleEvents();

	int Render(double t, double fdt);

	int Update(double t, double dt);

	int Cleanup() const;


	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event events = SDL_Event();
	Vector2Int screenSize = Vector2Int(800, 600);

	static double Now();
};


