

#include "Asteroid.h"
#include "TextureManager.h"
#include "GameObject.h"


int Asteroid::Split()
{
	std::cout << "splitting" << std::endl;
	isActive = false;

	return 0;
}

int Asteroid::Render(double alpha)
{
	if (isActive) {
		InterpolateState(alpha);

		SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, currentState.angle, NULL, flip);
	}

	return 0;
}


int Asteroid::Update(time_point t)
{
	if (isActive) {
		Move(t);
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
	double velocityX = 0;
	double velocityY = 0;
	double postitionX = 10;
	double postitionY = 10;
	const char* texture;
	switch (size) {
	case BIG:
		rectSize = 256;
		texture = "assets/bigAsteroids.png";
		break;
	case MID:
		rectSize = 128;
		texture = "assets/mediumAsteroids.png";
		break;
	case SMALL:
		rectSize = 64;
		texture = "assets/smallAsteroids.png";
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
	currentState.velocityX = velocity1;
	currentState.velocityY = velocity2;

	previousState = currentState;
	Integrate(currentState, t);
	return 0;
}

int Asteroid::Spawn()
{
	isActive = true;
	int randomNumber1 = 0;
	int randomNumber2 = 0;

	int wall = rand() % 2;

	std::cout << wall << std::endl;
	if (wall == 0)
	{
		randomNumber1 = 200;
		randomNumber2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 300) + 200);
		randomNumber2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 300) + 200);
		randomNumber2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 300) + 200);
		std::cout << randomNumber2 << std::endl;
	}
	if (wall == 1)
	{
		randomNumber1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 600) + 200);
		randomNumber2 = 200;
		std::cout << randomNumber1 << std::endl;
	}


	currentState.positionX = randomNumber1;
	currentState.positionY = randomNumber2;
	velocity1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2)-1);
	velocity2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2)-1);
	while (velocity1 == 0)
	{
		velocity1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2) - 1);
	}while (velocity2 == 0)
	{
		velocity2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2) - 1);
	}


//TODO the stuff from the constructor that makes the thing appear on screen should move here. Or this should be a mehtod to place it in the correct vector that gets rendered on screen (in Game.Render())
	return 0;
}



