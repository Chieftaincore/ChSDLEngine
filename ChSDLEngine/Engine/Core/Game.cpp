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
		if (event.type == SDL_QUIT) {
			m_IsRunning = true;
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
	if(m_Renderer) SDL_DestroyRenderer(m_Renderer);
	if(m_Window) SDL_DestroyWindow(m_Window);

	SDL_Quit();
}