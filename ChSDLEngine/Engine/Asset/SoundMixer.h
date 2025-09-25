#pragma once

#include <string>
#include <SDL_mixer.h>
#include <unordered_map>

using namespace std;

class SoundMixer
{
public:
	void Init() { Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); }
	void Shutdown();

	Mix_Chunk* GetSound(const string& key, const string& path = "");
	void PlayMix(const string& key, int multipleplay = 0) { Mix_PlayChannel(-1, GetSound(key), multipleplay); }


private:
	unordered_map<string, Mix_Chunk*> MixCache;

};

