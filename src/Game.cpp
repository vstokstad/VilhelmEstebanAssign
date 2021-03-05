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
	if (!SDL_CreateWindowAndRenderer(screenSize.x, screenSize.y, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer))
	{
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

double Game::Now()
{
	double time = (double)SDL_GetPerformanceCounter() * 1000 / (double)SDL_GetPerformanceFrequency();
	return time;
}



int Game::GameLoop()
{
//SET TIME START//
	double t = 0.0f;
	const double dt = 0.01f;
	double fdt = 0.02f;
	double accumulator = 0.0f;
/*	// the fps that the game is set at.
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;*/


	double end;
	StartGame();
	double frameTime;
	while (appRunning) {

		double start = Now();

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
		fdt = alpha;
		Render(t, alpha);

		end = Now();
		frameTime = end-start;

	/*	std::cout << "frameTime: "<< frameTime << " accumulator: " << accumulator <<" deltaTime : "<< dt << std::endl;
		std::cout << "alpha: "<< alpha << " time: " << t <<" fixedDeltaTime : "<< fdt << std::endl;*/

	}

	/*while (appRunning)
	{
		frameStart = SDL_GetTicks();

		//Check for input;
		HandleEvents();
		Update();
		Render();

		// this will get how many ticks have gone by on one loop or frame
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime){ SDL_Delay(frameDelay - frameTime); }
	}*/
	return 0;
}


int Game::HandleEvents()
{
	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_KEYDOWN) /*{ player->HandleInput(events); }*/
		if (events.key.type == SDL_KEYDOWN) {
			player->HandleInput(events.key);
		}

		//check if app is closing to quit.
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

	asteroid->Update(t,dt);
	return 0;
}

int Game::StartGame()
{



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



