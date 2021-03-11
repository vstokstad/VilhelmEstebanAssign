


#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Asteroid.h"

int Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	Vector2Int screenSize = Vector2Int(1200, 800);
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


int Game::GameLoop()
{
	StartGame();

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

		using namespace std::chrono;
		static auto t = time_point_cast<seconds>(steady_clock::now());
		static int frame_count = 0;
		static int frame_rate = 0;
		auto pt = t;

		t = time_point_cast<seconds>(steady_clock::now());
		++frame_count;
		if (t != pt) {
			frame_rate = frame_count;
			frame_count = 0;
		}
		std::cout << "Frame rate is " << frame_rate << " frames per second.  VelocityX = "
		          << player->currentState.velocityX << " m/s\n"
		          << " VelocityY = " << player->currentState.velocityY << " m/s\n";
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


int Game::Render(double alpha) const
{


	SDL_RenderClear(renderer);
	player->Render(alpha);
	asteroid->Render(alpha);

	//present the first render.
	SDL_RenderPresent(renderer);


	return 0;
}

int Game::Update(time_point t)
{

	HandleEvents();
	player->Update(t);
	asteroid->Update(t);
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



