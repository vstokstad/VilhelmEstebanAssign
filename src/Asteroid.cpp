

#include "Asteroid.h"
#include "TextureManager.h"
#include "GameObject.h"


int Asteroid::Split()
{
	std::cout << "splitting" << std::endl;
	isActive = false;
	if (hasChildren) {
		for (int i = 0; i < children.size(); ++i) {
			children[i]->Spawn();
		}
	}
	return 0;
}

int Asteroid::Render(double alpha)
{
	if (isActive) {
		InterpolateState(alpha);

		SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, currentState.angle, NULL, flip);
	}
	for (auto c:children) {
		{
			if (c->isActive) {
				c->Render(alpha);
			}
		}
	}
	return 0;
}


int Asteroid::Update(time_point t)
{
	if (isActive) {
		Move(t);
	}
	for (auto c:children) {
		if (c->isActive) {
			c->Move(t);
		}
	}
	return 0;
}

Asteroid::Asteroid(SDL_Renderer* renderer, AsteroidSize size)
{
	this->size = size;
	isActive = false;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	mRenderer = renderer;
	int rectSize;
	double velocityX = rand() / RAND_MAX;
	srand(time(NULL));
	double velocityY = rand() / RAND_MAX;
	double postitionX = (w / 2 * (rand() / RAND_MAX)) * 10;
	double postitionY = (h / 2 * (rand() / RAND_MAX)) * 10;
	const char* texture;
	switch (size) {
	case BIG:
		rectSize = 256;
		texture = "assets/bigAsteroids.png";
		hasChildren = true;
		for (auto& c:children) {
			c = new Asteroid(renderer, MID);
		}
		break;
	case MID:
		rectSize = 128;
		texture = "assets/mediumAsteroids.png";
		hasChildren = true;
		for (auto& c:children) {
			c = new Asteroid(renderer, SMALL);
		}
		break;
	case SMALL:
		rectSize = 64;
		texture = "assets/smallAsteroids.png";
		hasChildren = false;
		for (auto& c:children) {
			delete c;
		}
		break;
	default:
		texture = "assets/mediumAsteroids.png";
		rectSize = 128;
	}

	mDestRect = { static_cast<float>(postitionX), static_cast<float>(postitionY), static_cast<float>(rectSize),
	              static_cast<float>(rectSize) };
	mCollider = { static_cast<int>(postitionX), static_cast<int>(postitionY), rectSize / 2, rectSize / 2 };
	currentState = { 0, 0, velocityX, velocityY, postitionX, postitionY, 0, 0, 0 };
	previousState = { 0, 0, 0, 0, postitionX, postitionY, 0, 0, 0 };
	IMG_Init(IMG_INIT_PNG);


	mTexture = TextureManager::LoadTexture(texture, mRenderer);


}


int Asteroid::Move(time_point t)
{

	currentState.accelerationX = 0;
	currentState.accelerationY = 0;
	currentState.velocityX = 1;
	currentState.velocityY = 1;

	previousState = currentState;
	Integrate(currentState, t);
	return 0;
}

int Asteroid::Spawn()
{
	isActive = true;
	currentState.positionX = rand() / w;
	currentState.positionY = rand() / h;


//TODO the stuff from the constructor that makes the thing appear on screen should move here. Or this should be a mehtod to place it in the correct vector that gets rendered on screen (in Game.Render())
	return 0;
}



