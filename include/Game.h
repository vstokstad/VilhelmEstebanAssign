//
// Created by Vilhelm Stokstad on 2021-02-17.
//

#pragma once

#include "include.h"
#include "Player.h"
#include "GameObject.h"
#include "TextureManager.h"

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

	int Update();

	int Cleanup() const;

	GameObject* asteroid = new GameObject();
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event events = SDL_Event();
	Vector2Int screenSize = Vector2Int(800, 600);

};


