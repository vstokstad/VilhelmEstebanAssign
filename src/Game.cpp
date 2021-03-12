


#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Asteroid.h"

int Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "1");
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
	SDL_SetHint(SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP, "0");
	SDL_SetHint(SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN, "1");


	Vector2Int screenSize = Vector2Int(1200, 800);
	//CONSTRUCTOR AND WINDOW GETS MADE HERE//
	if (!SDL_CreateWindowAndRenderer(screenSize.x, screenSize.y, SDL_WINDOW_ALLOW_HIGHDPI || SDL_WINDOW_FULLSCREEN, &window, &renderer)) {
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


int Game::GameLoop()
{


//SET TIME START//

	using namespace std::literals;
	time_point t = {};
	time_point currentTime = Clock::now();
	duration accumulator = 0s;


	while (appRunning) {

		time_point newTime = Clock::now();
		auto frameTime = newTime - currentTime;
		if (frameTime > 0.25s)
			frameTime = 0.25s;

		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= dt) {
			Update(t);
			t += dt;
			accumulator -= dt;
		}

		const double alpha = std::chrono::duration<double>{ accumulator } / dt;

		Render(alpha);




	}
	return 0;
}


int Game::HandleEvents()
{
	while (SDL_PollEvent(&events)) {
		if (events.key.type == SDL_KEYDOWN || events.key.type == SDL_KEYUP) {
			player->HandleInput(events.key);
		}
		if (SDL_QUIT == events.type) { appRunning = false; }
	}
	return 0;
}


int Game::Render(double alpha) const
{


/*	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);*/
	SDL_RenderClear(renderer);

	player->Render(alpha);
	asteroid->Render(alpha);
	SDL_RenderPresent(renderer);

//DEBUG DRAWING
	/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRectF(renderer, &player->mDestRect);
	SDL_RenderDrawRectF(renderer, &asteroid->mDestRect);
	SDL_RenderDrawPointF(renderer, player->w / 2, player->h / 2);

	SDL_RenderDrawRect(renderer, &player->mCollider);
	SDL_RenderDrawRect(renderer, &asteroid->mCollider);

	SDL_RenderDrawLine(renderer, 0, 0, player->w, player->h);
	SDL_RenderDrawLine(renderer, player->w, 0, 0,player->h );

	SDL_RenderPresent(renderer);*/


	return 0;
}

int Game::Update(time_point t)
{

	HandleEvents();
	player->Update(t);
	asteroid->Update(t);
	if (player->CollisionDetection(&asteroid->mCollider) == 1) {
		ShowGameOverScreen();
	}
	return 0;
}

int Game::StartGame()
{

this->Init();
this->GameLoop();

	asteroid->Spawn();

	return 0;
}

int Game::ShowGameOverScreen()
{
	//TODO add text or sprites for a gameOver screen;
	std::cout << "GAME OVER" << std::endl;
	RestartGame();
	return 0;
}

int Game::RestartGame()
{
	SDL_Delay(1000);
	player->~Player();
	asteroid->~Asteroid();
	SDL_RenderClear(renderer);
	StartGame();
	return 0;
}

int Game::Cleanup() const
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	player->~Player();
	asteroid->~Asteroid();
	IMG_Quit();
	SDL_Quit();
	return 0;
}



