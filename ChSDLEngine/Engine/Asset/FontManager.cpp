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

/// <summary>
/// ENG Deletes the old Cache And Texture then Returns the New Texture so there will be no Dangling points or Memory Leak
/// Use it for continously Updating Fonts.
/// </summary>
/// <returns>Returns the New texture</returns>
SDL_Texture* FontManager::ContuniousUpdateText(const string& oldtext ,const string& text, const string& fontPath, int ptSize, SDL_Color color) {

	const string oldcachekey = text + "|" + fontPath + "|" + to_string(ptSize);

		SDL_DestroyTexture(TextCacheMap[oldcachekey]);
		TextCacheMap.erase(oldcachekey);

		cout << "[Erased Cache] : " << oldcachekey << endl;
		cout << "[Destroyed Texture] : " << oldcachekey << endl;
	

	SDL_Texture* Texture = GetTextTexture(text, fontPath, ptSize, color);

	return Texture;
}

void FontManager::Shutdown() {

	for (auto& ctd : TextCacheMap) SDL_DestroyTexture(ctd.second);
	for (auto& ftd : FontsMap) TTF_CloseFont(ftd.second);

	TextCacheMap.clear();
	FontsMap.clear();

	TTF_Quit();
}