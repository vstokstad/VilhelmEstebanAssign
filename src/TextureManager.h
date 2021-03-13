#pragma once

#include "SDL_image.h"
#if __cplusplus == 201703L
#define CXX17 = TRUE
#include <filesystem>
namespace fs = std::filesystem;
#include <unordered_map>
#endif


class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren)
	{
		SDL_Surface* tempSurface = IMG_Load(texture);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
		SDL_FreeSurface(tempSurface);
		return tex;
	}


	//STARTED DOING SOME STUFF TO DYNAMICALLY LOAD ALL TEXTURES AT START OF GAME:::
#ifdef CXX17
	static SDL_Texture*	GetTexture(const char* name, SDL_Renderer* renderer, std::unordered_map<std::string, SDL_Surface> surfaces)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, &surfaces.at(name));
		return texture;

	}

	static std::unordered_map<std::string, SDL_Surface> LoadAssets()
	{
		auto path = "./assets/";
		std::unordered_map<std::string, SDL_Surface> surfaces;
		for (const auto& entry : fs::directory_iterator(path)) {
			auto* localPath = new char[entry.path().string().size() + 1];
			memcpy(localPath, entry.path().c_str(), entry.path().string().size() + 1);
			SDL_Surface* surf = IMG_Load(localPath);
			surfaces.emplace(localPath, *surf);
			std::cout << path << std::endl;
		}
		return surfaces;
	}
#endif
};


