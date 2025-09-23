#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>

using namespace std;

struct SpriteImage {
	SDL_Texture* textr = nullptr;
	SDL_Rect dst{ 0,0,0,0 };
	SDL_Rect src{ 0,0,0,0 };
	int sortIndex{ 0 };
};

class RenderQueue
{
public:
	void Add(const SpriteImage& s) { m_Sprites.emplace_back(s); }
	void Clear() {
		m_Sprites.clear();
	}

	void Shuffle(SDL_Renderer* render) {

		sort(m_Sprites.begin(), m_Sprites.end()
			, [](const SpriteImage& s1, const SpriteImage& s2) {
				return s1.sortIndex < s2.sortIndex;
			}
		);

		for (const auto& s : m_Sprites) 
			SDL_RenderCopy(render, s.textr,( s.src.w ? &s.src : nullptr), &s.dst);

		m_Sprites.clear();
	}

private:
	vector<SpriteImage> m_Sprites;

};
