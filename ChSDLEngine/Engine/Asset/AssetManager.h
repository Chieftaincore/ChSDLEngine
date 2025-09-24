#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_render.h>

#include <unordered_map>
#include <string>

using namespace std;

class AssetManager {

public:
	void Init(SDL_Renderer* render);
	void Shutdown();

	SDL_Texture* GetTexture(const string& key, const string& filePath);
	Mix_Chunk* GetSoundMix(const string& lName);

private:
	SDL_Renderer* Renderer = nullptr;

	unordered_map<string, SDL_Texture*> AssetTextures;
	unordered_map<string, Mix_Chunk*> AssetMixSounds;
};