#include "AssetManager.h"
#include <iostream>

void AssetManager::Init(SDL_Renderer* rn) {

	Renderer = rn;
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void AssetManager::Shutdown() {

	for (auto& textodes : AssetTextures) 
		SDL_DestroyTexture(textodes.second);
	
	AssetTextures.clear();
	IMG_Quit();
}

SDL_Texture* AssetManager::GetTexture(const string& key, const string& filePath) 
{

	if (auto it = AssetTextures.find(key); it != AssetTextures.end())
		return it->second;

	const string file = filePath.empty() ? key : filePath;

	SDL_Surface* surfc = IMG_Load(file.c_str());

	if (!surfc) {
		cerr << "Ooops Something went wrong on IMG_LOAD :: " << IMG_GetError() << endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surfc);
	SDL_FreeSurface(surfc);

	if (!texture) {
		cerr << "Ooops Something went wrong on Texture Creation :: " << SDL_GetError() << endl;
		return nullptr;
	}

	AssetTextures[key] = texture;
	return texture;

}