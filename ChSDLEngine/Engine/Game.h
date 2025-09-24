#pragma once
#include<string>
#include<SDL.h>
#include<SDL_image.h>

#include "Core/PhysicsB2d.h"
#include "Core/RenderQueue.h"
#include "Asset/FontManager.h"
#include "Asset/AssetManager.h"
#include "Objects/Placeholder.h"
#include "Core/SpriteAnimation.h"

using namespace std;

constexpr float m_PPM = 100.f;

class Game
{
	//ENG Mainframe Stuff / TUR Ana-Çerçeve
public:
	Game();
	~Game();
	bool Init(const string& title, int width, int height);
	void Run();
	void Shutdown();

	//ENG Game-Loop Functions / TUR Oyun Döngüsü Fonksiyonlar
private:
	void InputProcess();
	void Update(float Delta);
	void Render();

	//ENG Functions / TUR Çekirdek Fonksiyonlar
private:

	//ENG temporary before Objects/Entity implemantations.
	void StartingProcedures();

	void ToggleFullScreen();
	SDL_Texture* LoadTexture(const string& path);

	//Variables / TUR Deðiþkenler
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	PhysicsB2d Physics;
	RenderQueue RQ;
	AssetManager AM;
	FontManager FM;

	SDL_Texture* FPS_FontTexture = nullptr;
	SDL_Rect FPS_TextRect = {12,12,0,0};

	sAnimationClip aClip;
	AnimatedSprite aSprite;
	AnimationSystem animationSystem;

	Placeholder* placeholder = new Placeholder(m_PPM);
	Placeholder* placeholder2 = new Placeholder(m_PPM);

	bool m_IsRunning = false;

	bool m_IsFullScreen = false;
	int m_WindowWidth = 800;
	int m_WindowHeight = 600;

};