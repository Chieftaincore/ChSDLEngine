#include "FontManager.h"
#include <iostream>

TTF_Font* FontManager::GetFont(const string& path, int punto) {
	FontKey k{ path, punto };

	if(auto it = FontsMap.find(k); it != FontsMap.end()) return it->second;

	TTF_Font* f = TTF_OpenFont(path.c_str(), punto);
	if (!f) {

		cerr << "Error on TTF_OpenFont :: " << TTF_GetError() << endl;
		return nullptr;
	}

	FontsMap[k] = f;
	return f;
}

SDL_Texture* FontManager::GetTextTexture(const string& text, const string& fontPath, int ptSize, SDL_Color color) {

	const string cachekey = text + "|" + fontPath + "|" + to_string(ptSize);

	if (auto it = TextCacheMap.find(cachekey); it != TextCacheMap.end())
		return it->second;

	TTF_Font* font = GetFont(fontPath, ptSize);
	if (!font) {
		cerr << "Error on Font proccessing GetFont :" << TTF_GetError() << endl;
		return nullptr;
	}

	SDL_Surface* surf = TTF_RenderText_Blended(font, text.c_str(), color);
	
	if (!surf) {
		cerr << "Error on Rendering Text TTF_RenderText_Blended : " << TTF_GetError() << endl;
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surf);
	SDL_FreeSurface(surf);

	TextCacheMap[cachekey] = texture;
	return texture;
}

void FontManager::Shutdown() {

	for (auto& ctd : TextCacheMap) SDL_DestroyTexture(ctd.second);
	for (auto& ftd : FontsMap) TTF_CloseFont(ftd.second);

	TextCacheMap.clear();
	FontsMap.clear();

	TTF_Quit();
}