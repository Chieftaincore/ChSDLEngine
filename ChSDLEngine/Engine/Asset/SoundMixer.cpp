#include "SoundMixer.h"
#include <iostream>

Mix_Chunk* SoundMixer::GetSound(const string& key, const string& path) {

	auto it = MixCache.find(key); if (it != MixCache.end()) return it->second;

	Mix_Chunk* c = Mix_LoadWAV(path.empty() ? key.c_str() : path.c_str());

	if (!c) {
		cerr << "Error On Mix_LoadWAV : " << Mix_GetError() << endl; 
		return nullptr;
	}

	MixCache[key] = c;
	return c;
}


void SoundMixer::Shutdown() {
	
	for (auto& mtd : MixCache) Mix_FreeChunk(mtd.second);

	Mix_CloseAudio();
	MixCache.clear();
}