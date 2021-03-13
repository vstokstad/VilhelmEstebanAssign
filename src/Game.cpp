


#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Asteroid.h"
#include "Bullet.h"

int Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);

	appRunning = true;
	Vector2Int screenSize = Vector2Int(1200, 800);
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "1");
	//CONSTRUCTOR AND WINDOW GETS MADE HERE//
	if (SDL_CreateWindowAndRenderer(screenSize.x, screenSize.y,
			SDL_WINDOW_ALLOW_HIGHDPI, &window,
			&renderer) != 0) {
		// In the case that the window could not be made...
		if (window == nullptr || renderer == nullptr) {
			SDL_Quit();
			appRunning = false;
			return 1;
		}

	}


	//draw the window//
	SDL_ShowWindow(window);
	SDL_RaiseWindow(window);

	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	//initialize the player//
	player = new Player(renderer);
	asteroid = new Asteroid(renderer);

	//present the first render.
	SDL_RenderPresent(renderer);

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

		//Framerate stuff:
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
			std::cout << "Frame rate is " << frame_rate << " frames per second." << std::endl;
		}
	}
	return 0;
}


int Game::HandleEvents()
{
	while (SDL_PollEvent(&events)) {
		if (events.key.type == SDL_KEYDOWN || events.key.type == SDL_KEYUP) {
			if (events.key.keysym.sym == SDLK_q) {
				appRunning = false;
			}
			if (events.key.keysym.sym == SDLK_r) {
				appRunning = false;
				RestartGame();
			}
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
	for (auto b : player->bullets) {
		if (b.isActive) {
			b.Render(alpha);
		}
	}
	SDL_SetRenderDrawColor(renderer, 255, 20, 40, 250);
	SDL_RenderDrawLine(renderer, player->currentState.positionX, player->currentState.positionY,
			player->currentState.directionX, player->currentState.directionY);
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);

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
	for (auto& b : player->bullets) {
		if (b.isActive) {
			b.Update();
			b.CollisionDetection(asteroid);
		}
	}


	return 0;
}

int Game::StartGame()
{

	this->Init();
	this->GameLoop();


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
	std::cout << "RESTARTING" << std::endl;
	player->~Player();
	asteroid->~Asteroid();
	SDL_RenderClear(renderer);
	SDL_PumpEvents();
	while (SDL_PollEvent(&events) != 0) {
		SDL_FlushEvent(events.type);
	}

	StartGame();
	return 0;
}

int Game::Cleanup() const
{
	std::cout << "QUITTING" << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	player->~Player();
	asteroid->~Asteroid();
	SDL_ShowCursor(1);
	IMG_Quit();
	SDL_Quit();
	return 0;
}



