

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
	currentState.velocityX = velocity1*2;
	currentState.velocityY = velocity2*2;

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

	if (wall == 0)
	{
		float tempRandomNumber1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / w));
		float tempRandomNumber2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / h));

		randomNumber1 = tempRandomNumber1;
		randomNumber2 = tempRandomNumber2;
	}
	if (wall == 1)
	{
		float tempRandomNumber1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / w));
		float tempRandomNumber2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / h));

		randomNumber2 = tempRandomNumber1;
		randomNumber2 = tempRandomNumber2;
	}

	currentState.positionX = randomNumber1;
	currentState.positionY = randomNumber2;
	
	float tempVelocity1 = rand() % 360;
	float tempVelocity2 = rand() % 360;
	velocity1 = sin(tempVelocity1)*2;
	velocity2 = cos(tempVelocity2) * 2;

	std::cout << tempVelocity1 << std::endl;
	std::cout << tempVelocity2 << std::endl;
	std::cout << velocity1 << std::endl;
	std::cout << velocity2 << std::endl;


	return 0;
}



