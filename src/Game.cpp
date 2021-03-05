//
// Created by Vilhelm Stokstad on 2021-02-17.
//


#include "Game.h"


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
	player = new Player();
	player->Init(renderer);
	asteroid = new GameObject("assets/bigAsteroid.png", renderer, 0, 0);

	//present the first render.
	SDL_RenderPresent(renderer);

	appRunning = true;
	return 0;
}

double Game::Now()
{
	auto time = SDL_GetTicks() ;
	return time;
}



int Game::GameLoop()
{
//SET TIME START//
	double t = 0.0f;
	const double dt = 1.0f;
	double fdt = 1.0f;
	double accumulator = 0.0f;
	// the fps that the game is set at.
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;


	double currentTime = Now();
	StartGame();

	while (appRunning) {

		double newTime = Now();
		double frameTime = newTime - currentTime;
		currentTime = newTime;
		std::cout << frameTime << std::endl;
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
		const double alpha = accumulator / dt;
		//fdt = alpha*fdt;
		Render(t, fdt);
	}

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
		if (events.key.type == SDL_KEYDOWN) {
			player->HandleInput(events.key);
		}
		if (events.button.type == SDL_MOUSEBUTTONDOWN) {
			r = events.button.x;
			b = events.button.y;
			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			//Set and render a new color//
			SDL_RenderClear(renderer);
		}
		//check if app is closing to quit.
		if (SDL_QUIT == events.type) { appRunning = false; }
	}
	return 0;
}

int Game::Render() const
int Game::Render(double t, double fdt)
{
	SDL_RenderClear(renderer);
	player->Rendering();
	if (!asteroid->Render()){}

	player->Rendering(t, fdt);
	player->Rendering(0.0, 1.0);
	//present the first render.
	SDL_RenderPresent(renderer);

	return 0;
}

int Game::Update(double t, double dt)
{

	player->Update(t, dt);

	asteroid->Update();
	player->Update();
	return 0;
}

int Game::StartGame()
{


	std::cout << asteroid->mXpos << std::endl;
	std::cout << asteroid->mYpos << std::endl;
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



