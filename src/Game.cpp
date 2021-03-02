//
// Created by Vilhelm Stokstad on 2021-02-17.
//


#include "Game.h"


int Game::Init()
{


	SDL_Init(SDL_INIT_EVERYTHING);

	screenSize = new Vector2Int(800, 600);

	//CONSTRUCTOR AND WINDOW GETS MADE HERE//
	if (!SDL_CreateWindowAndRenderer(screenSize->x, screenSize->y, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer)){
		if (window == nullptr) {
			// In the case that the window could not be made...

		}
		if (renderer == nullptr) {
			// In the case that the window could not be made...

		}
	}




	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	player = new Player();
	player->Init(renderer);


	appRunning = true;
	return 0;
}


int Game::GameLoop()
{


	while (appRunning) {
		//Check for input;
		HandleEvents();

		Update();

		//Render the screen
		Render();

	}
	return 0;
}


int Game::HandleEvents()
{
	//Colors just for fun//
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
//get the current color//
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);

	while (SDL_PollEvent(&events)) {
		if (events.type == SDL_KEYDOWN) {
			player->HandleInput(events);
		}
		if (events.button.type == SDL_MOUSEBUTTONDOWN) {
			r = events.button.x;
			b = events.button.y;
			SDL_SetRenderDrawColor(renderer, r, g, b, a);
			//Set and render a new color//
			SDL_RenderClear(renderer);
		}
		//check if app is closing to quit.
		if (SDL_QUIT == events.type) {


			appRunning = false;

		}
	}
	return 0;

}

int Game::Render()
{

	SDL_RenderClear(renderer);


	player->Rendering();

	SDL_RenderPresent(renderer);

	return 0;
}

int Game::Update()
{
	player->Update();
	return 0;
}


int Game::Cleanup() const
{

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
return 0;
}


