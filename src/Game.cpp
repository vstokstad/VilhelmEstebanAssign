//
// Created by Vilhelm Stokstad on 2021-02-17.
//


#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <iostream>

GameObject* Asteroid;



int Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	screenSize = new Vector2Int(800, 600);

	//CONSTRUCTOR AND WINDOW GETS MADE HERE//
	if (!SDL_CreateWindowAndRenderer(screenSize->x, screenSize->y, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer)) 
	{
		// In the case that the window could not be made...
		if (window == nullptr) { return 1; }
		if (renderer == nullptr) { return 1; }
	}

	player->Init(renderer);

	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);
	SDL_RenderPresent(renderer);

	appRunning = true;
	return 0;
}


int Game::GameLoop()
{
	// the fps that the game is set at.
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	StartGame();
	
	while (appRunning) 
	{
		frameStart = SDL_GetTicks();

		//Check for input;
		HandleEvents();
		Update();
		Render();

		// this will get how many ticks have gone by on one loop or frame
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime){ SDL_Delay(frameDelay - frameTime); }
	}
	return 0;
}


int Game::HandleEvents()
{
	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_KEYDOWN) { player->HandleInput(events); }
		//check if app is closing to quit.
		if (SDL_QUIT == events.type) { appRunning = false; }
	}
	return 0;
}

int Game::Render() const
{
	SDL_RenderClear(renderer);
	player->Rendering();
	Asteroid->Render();
	SDL_RenderPresent(renderer);
	return 0;
}

int Game::Update() const
{
	player->Update();
	return 0;
}

int Game::StartGame() 
{
	Asteroid = new GameObject("assets/bigAsteroid.png", renderer);

	std::cout << Asteroid->xpos << std::endl;
	std::cout << Asteroid->ypos << std::endl;
	return 0;
}


int Game::Cleanup() const
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}


