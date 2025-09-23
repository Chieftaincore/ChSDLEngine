#pragma once
#include<string>
#include<SDL.h>
#include<SDL_image.h>

#include "PhysicsB2d.h"
#include "../Objects/Placeholder.h"

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
	void ToggleFullScreen();
	SDL_Texture* LoadTexture(const string& path);

	//Variables / TUR Deðiþkenler
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	PhysicsB2d Physics;

	Placeholder* placeholder = new Placeholder(m_PPM);

	bool m_IsRunning = false;

	bool m_IsFullScreen = false;
	int m_WindowWidth = 800;
	int m_WindowHeight = 600;

};