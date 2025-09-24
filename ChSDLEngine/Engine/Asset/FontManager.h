#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>

#include <string>

using namespace std;

struct FontKey { string path; int size; };

inline bool operator == (const FontKey& a, const FontKey& b) {
	return a.path == b.path && a.size == b.size;
}

struct FontKeyHash
{
	size_t operator() (const FontKey& k) const noexcept{
		return hash<string>{}(k.path) ^ (k.size < 2);
	}
};

class FontManager {

	public:
		void Init(SDL_Renderer* r) { Renderer = r; TTF_Init(); };
		void Shutdown();

		TTF_Font* GetFont(const string& path, int ptSize);
		SDL_Texture* GetTextTexture(const string& text, const string& fontPath, int ptSize, SDL_Color color = {255,255,255,255});


private:
	SDL_Renderer* Renderer = nullptr;

	unordered_map<FontKey, TTF_Font*, FontKeyHash> FontsMap;
	unordered_map<string, SDL_Texture* > TextCacheMap;
};