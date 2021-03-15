


#include "Game.h"
#include "Player.h"
#include "GameObject.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "TextureManager.h"

int Game::Init()
{
	srand(time(0));
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
	const char* bg = "assets/background.png";
	backgroundTexture = TextureManager::LoadTexture(bg, renderer);
	//draw the window//
	SDL_ShowWindow(window);
	SDL_RaiseWindow(window);

	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	//initialize the player//
	player = new Player(renderer);
	//asteroid = new Asteroid(renderer, BIG);

	//present the first render.
	SDL_RenderPresent(renderer);

	for (auto& i : bigAst) {
		i = new Asteroid(renderer, BIG);
		std::cout << i << std::endl;
		ActiveAst.push_front(i);
	}

	for (auto& i : midAst) {
		i = new Asteroid(renderer, MID);
		ActiveAst.push_back(i);
	}
	for (auto& i : smallAst) {
		i = new Asteroid(renderer, SMALL);
		ActiveAst.push_back(i);
	}

	return 0;
}


int Game::GameLoop()
{


//SET TIME START//

	using namespace std::literals;
	time_point t = {};
	time_point currentTime = Clock::now();
	duration accumulator = 0s;

	//asteroid->Spawn();
	for (auto& i : ActiveAst) {


		i->Spawn();
	}
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
			//std::cout << "Frame rate is " << frame_rate << " frames per second." << std::endl;
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

// ALL THE DrawRects below are for debugging and draws the respective objects collider;
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
	SDL_SetRenderDrawColor(renderer, 255, 20, 40, 250);
	player->Render(alpha);
	for (auto b : player->bullets) {
		if (b.isActive) {
			b.Render(alpha);
		}
	}
	for (auto a:ActiveAst) {
		if (a->isActive) {
			a->Render(alpha);
		}


	}

	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 30, 20, 40, 250);
	return 0;
}

int Game::Update(time_point t)
{

	HandleEvents();
	player->Update(t);
	for (auto& i : ActiveAst) {
		i->Update(t);
	}
	//asteroid->Update(t);
	CollisonCheck();


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

	//asteroid->~Asteroid();
	ActiveAst.clear();
	for (auto& i : ActiveAst) {
		i->~Asteroid();
	}
	SDL_RenderClear(renderer);
	SDL_PumpEvents();
	while (SDL_PollEvent(&events) != 0) {
		SDL_FlushEvent(events.type);
	}
	SDL_Quit();

	StartGame();
	return 0;
}

int Game::Cleanup() const
{
	std::cout << "QUITTING" << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	player->~Player();
	for (auto& i : ActiveAst) {
		i->~Asteroid();
	}
	SDL_ShowCursor(1);
	IMG_Quit();
	SDL_Quit();
	return 0;
}

int Game::CollisonCheck()
{
	for (auto& ast : ActiveAst) {
		if (player->CollisionDetection(ast) == 1) {
			ShowGameOverScreen();
			break;
		}
		for (auto& b : player->bullets) {
			if (b.isActive) {
				b.Update();
				b.CollisionDetection(ast);
			}
		}
	}
	return 0;
}


