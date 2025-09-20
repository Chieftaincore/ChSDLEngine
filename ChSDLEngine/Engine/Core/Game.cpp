#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() {}

Game::~Game() {
	Shutdown();
}

bool Game::Init(const string& title, int width, int height) {
	m_WindowWidth = width;
	m_WindowHeight = height;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "SDL_INIT Failed || ERROR : " << SDL_GetError() << endl;
		return false;
	}

	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_WindowWidth, m_WindowHeight, SDL_WINDOW_SHOWN);

	if (!m_Window) {
		cerr << "Oops Something went wrong on Window Creation || ERROR : " << SDL_GetError() << endl;
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if (!m_Renderer) {
		cerr << "Something went wrong on Renderer Creation || ERROR : " << SDL_GetError() << endl;
		return false;
	}

	m_IsRunning = true;
	return true;
}

void Game::Run() {
	while (m_IsRunning) {
		InputProcess();
		Update(0.016f);
		Render();
	}
}

void Game::InputProcess() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {

		switch (event.type) {

		case SDL_QUIT:
			cout << "[EVENT] | QUIT EVENT" << endl;
			m_IsRunning = false;
			Shutdown();
			break;

		case SDL_KEYDOWN:

			cout << "[EVENT] | Key Pressed Down : " << SDL_GetKeyName(event.key.keysym.sym) << endl;
			
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				Shutdown();
				break;
			
			case SDLK_F11:
				ToggleFullScreen();
				break;
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			cout << "[EVENT] | Key Released : " << SDL_GetKeyName(event.key.keysym.sym) << endl;
			break;

		case SDL_MOUSEMOTION:
			cout << "[EVENT] | Mouse Movement : " << event.motion.x << ", " << event.motion.y << endl;
			break;

		case SDL_MOUSEBUTTONDOWN:
			cout << "[EVENT] | Mouse Pressed : " << event.button.button << " | " << event.button.x << ", " << event.button.y << endl;
			break;
		}


	}
}

void Game::Update(float) {
	//Game Logic will go here
}

void Game::Render() {

	SDL_SetRenderDrawColor(m_Renderer, 90,30,30,255);
	SDL_RenderClear(m_Renderer);
	SDL_RenderPresent(m_Renderer);
}

void Game::Shutdown() {

	if (m_Renderer) { 
		SDL_DestroyRenderer(m_Renderer); 
		m_Renderer = nullptr;
	}

	if (m_Window) {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	} 

	SDL_Quit();
}

void Game::ToggleFullScreen() {

	//ENG this Fullscreen is Bordeless Window. for Native Fulscreen delete Desktop part
	if (!m_IsFullScreen) {
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(m_Window, 0);
	}
	m_IsFullScreen = !m_IsFullScreen;
}