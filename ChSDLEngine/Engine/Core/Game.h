#pragma once

#include<string>
#include<SDL.h>

using namespace std;

class Game
{

	//ENG Mainframe Stuff
public:
	Game();
	~Game();
	bool Init(const string& title, int width, int height);
	void Run();
	void Shutdown();

	//ENG Functions
private:
	void InputProcess();
	void Update(float Delta);
	void Render();

	//ENG Variables
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	bool m_IsRunning = false;
	int m_WindowWidth = 800;
	int m_WindowHeight = 600;

};