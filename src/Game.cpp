//
// Created by Vilhelm Stokstad on 2021-02-17.
//


#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Asteroid.h"

int Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);


	//CONSTRUCTOR AND WINDOW GETS MADE HERE//
	if (!SDL_CreateWindowAndRenderer(screenSize.x, screenSize.y, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer)) {
		// In the case that the window could not be made...
		if (window == nullptr) { return 1; }
		if (renderer == nullptr) { return 1; }
	}
//draw the window//
	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);
	SDL_RenderClear(renderer);
	//initialize the player//
	player = new Player(renderer);
	asteroid = new Asteroid(renderer);
	//present the first render.
	SDL_RenderPresent(renderer);

	appRunning = true;
	return 0;
}

uint64_t Game::Now()
{
	uint64_t time = SDL_GetPerformanceCounter();
	return time;
}


int Game::GameLoop()
{
	StartGame();

//SET TIME START//
	double t = 0.0;
	const double dt = 1.0/60.0;
	double fdt = 0.02;
	double accumulator = 0.0;
	uint64_t end = .0;
	double frameTime = .0;

	while (appRunning) {

		uint64_t newTime = Now();

		if (frameTime > 0.25) {
			frameTime = 0.25;
		}

		accumulator += frameTime;
		while (accumulator >= dt) {
			HandleEvents();
			Update(t, dt);
			t += dt;
			accumulator -= dt;
		}
		double alpha = accumulator / dt;

		Render(t, fdt);

		end = Now();
		frameTime = (double)((end - newTime)) / (double)SDL_GetPerformanceFrequency();

	}
	return 0;
}


int Game::HandleEvents()
{
	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_KEYDOWN) /*{ player->HandleInput(events); }*/
			if (events.key.type == SDL_KEYDOWN) {
				player->HandleInput(events.key);
			}
		if (SDL_QUIT == events.type) { appRunning = false; }
	}
	return 0;
}


int Game::Render(double t, double fdt) const
{
	SDL_RenderClear(renderer);
	player->Render(t, fdt);
	asteroid->Render(t, fdt);

	//present the first render.
	SDL_RenderPresent(renderer);

	return 0;
}

int Game::Update(double t, double dt)
{

	player->Update(t, dt);
	asteroid->Update(t, dt);
	return 0;
}

int Game::StartGame()
{


	asteroid->Spawn();

	return 0;
}


int Game::Cleanup() const
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	player->~Player();
	IMG_Quit();
	SDL_Quit();
	return 0;
}



