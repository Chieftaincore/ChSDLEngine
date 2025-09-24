#include "Game.h"
#include <iostream>

using namespace std;

constexpr int CORE_TARGET_FPS = 60;
constexpr int FRAME_DELAY = 1000 / CORE_TARGET_FPS;

Game::Game() {}

Game::~Game() {
	Shutdown();
}

bool Game::Init(const string& title, int width, int height) {
	 
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG); // TUR SDL_Image Processor yüklenmesi için.

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
	
	Physics.Init(m_PPM, 0.f, 0.f);

	//Asset Manager
	AM.Init(m_Renderer);

	//Font Manager
	FM.Init(m_Renderer);

	StartingProcedures();

	m_IsRunning = true;
	return true;
}

void Game::Run() {

	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 _Freq = SDL_GetPerformanceFrequency();

	Uint32 _FPSTimer = SDL_GetTicks();
	int _FPSCount = 0;

	while (m_IsRunning) {

		Uint64 elNow = SDL_GetPerformanceCounter();
		float dTime = static_cast<float> (elNow - now) / _Freq;
		now = elNow;

		Uint32 frameStart = SDL_GetTicks();
		_FPSCount++;

		InputProcess();
		Update(dTime);
		Render();
		
		Uint32 elapsed = SDL_GetTicks() - frameStart;

		if (elapsed < FRAME_DELAY) {
			SDL_Delay(FRAME_DELAY - elapsed);
		}

		if (SDL_GetTicks() - _FPSTimer > 1000) {
		
			//ENG!!!! This causes to FPStimer on screen to behave inconsistent but without it there will be a lots of memory will be written for no reason
			SDL_DestroyTexture(FPS_FontTexture);
			//So a solution is needed preferly within the FontManager.

			cout << "[FPS Timer] FPS :" << _FPSCount  << endl;

			string txt = "[FPS] : " + to_string(_FPSCount);

			FPS_FontTexture = FM.GetTextTexture(txt, "Assets/Fonts/Roboto-Bold.ttf", 12);
			SDL_QueryTexture(FPS_FontTexture, nullptr, nullptr, &FPS_TextRect.w, &FPS_TextRect.h);

			_FPSCount = 0;
			_FPSTimer += 1000;
		}

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

		const Uint8* keys = SDL_GetKeyboardState(nullptr);

		placeholder->InputDir = { 0.0f, 0.0f };

		if (keys[SDL_SCANCODE_W]) placeholder->InputDir.y = -1.f;
		if (keys[SDL_SCANCODE_D]) placeholder->InputDir.x = 1.f;
		if (keys[SDL_SCANCODE_S]) placeholder->InputDir.y = 1.f;
		if (keys[SDL_SCANCODE_A]) placeholder->InputDir.x = -1.f;

		placeholder2->InputDir = { 0.0f, 0.0f };

		if (keys[SDL_SCANCODE_UP]) placeholder2->InputDir.y = -1.f;
		if (keys[SDL_SCANCODE_RIGHT]) placeholder2->InputDir.x = 1.f;
		if (keys[SDL_SCANCODE_DOWN]) placeholder2->InputDir.y = 1.f;
		if (keys[SDL_SCANCODE_LEFT]) placeholder2->InputDir.x = -1.f;
	}
}

void Game::Update(float dTime) {
	
	Physics.Step(dTime);

	placeholder->Move(dTime);
	placeholder2->Move(dTime);

	animationSystem.Update(dTime);

}

void Game::Render() {

	SDL_SetRenderDrawColor(m_Renderer, 90,30,30,255);
	SDL_RenderClear(m_Renderer);
	RQ.Clear();

	aSprite.Draw(RQ, 5);

	placeholder->plchDsT.x = static_cast<int>(placeholder->Position.x);
	placeholder->plchDsT.y = static_cast<int>(placeholder->Position.y);
	placeholder2->plchDsT.x = static_cast<int>(placeholder2->Position.x);
	placeholder2->plchDsT.y = static_cast<int>(placeholder2->Position.y);

	RQ.Add({ FPS_FontTexture, FPS_TextRect, SDL_Rect{0,0,0,0}, 200});
	RQ.Add({placeholder->Texture, placeholder->plchDsT, SDL_Rect{0,0,0,0}, 10});
	RQ.Add({placeholder2->Texture, placeholder2->plchDsT, SDL_Rect{0,0,0,0}, 10});

	RQ.Shuffle(m_Renderer);

	SDL_RenderPresent(m_Renderer);
}

void Game::StartingProcedures() {

	placeholder->SetTexture(AM.GetTexture("test", "Assets/Images/test.jpg"));
	placeholder2->SetTexture(AM.GetTexture("test", "Assets/Images/test.jpg"));

	SDL_Texture* AnimatedSprite = AM.GetTexture("colorsanim","Assets/Images/spriteanimtest.png");
	const int w = 90, h = 90, frames = 4;


	for (int i = 0; i < frames; i++) {
		aClip.frames.push_back({i * w,0,w,h});
	}

	aClip.tex = AnimatedSprite;
	aClip.animFPS = 6.f;

	aSprite.SetClip(&aClip);
	aSprite.x = 600;
	aSprite.y = 400;

	animationSystem.Add(&aSprite);

	placeholder->BodyInsId = Physics.CreateBox(
		placeholder->Position.x + placeholder->plchDsT.w / 2,
		placeholder->Position.y + placeholder->plchDsT.h / 2,
		(float)placeholder->plchDsT.w, (float)placeholder->plchDsT.h,
		true, 1.f, 0.8f);

	placeholder2->MoveSpeed = 2.0f;
	placeholder2->Position.x = 500;
	placeholder2->Position.y = 400;

	placeholder2->BodyInsId = Physics.CreateBox(
		placeholder2->Position.x + placeholder2->plchDsT.w / 2,
		placeholder2->Position.y + placeholder2->plchDsT.h / 2,
		(float)placeholder2->plchDsT.w, (float)placeholder2->plchDsT.h,
		true, 1.f, 0.8f);

	Physics.CreateBox(m_WindowWidth / 2, 0, m_WindowWidth, 10, false);
	Physics.CreateBox(m_WindowWidth / 2, m_WindowHeight, m_WindowWidth, 10, false);
	Physics.CreateBox(0, m_WindowHeight / 2, 10, m_WindowHeight, false);
	Physics.CreateBox(m_WindowWidth, m_WindowHeight / 2, 10, m_WindowHeight, false);

}

void Game::Shutdown() {

	AM.Shutdown();

	if (m_Renderer) { 
		SDL_DestroyRenderer(m_Renderer); 
		m_Renderer = nullptr;
	}

	if (m_Window) {
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	} 

	Physics.Shutdown();

	FM.Shutdown();

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

SDL_Texture* Game::LoadTexture(const string& path) {

	SDL_Surface* Surface = IMG_Load(path.c_str());

	if (!Surface) {
		cerr << "Something went wrong on Texture Loading ERROR : IMG_Load | " << IMG_GetError() << endl;
		return nullptr;
	}

	SDL_Texture* Texture = SDL_CreateTextureFromSurface(m_Renderer, Surface);
	SDL_FreeSurface(Surface);

	if (!Texture) {
		cerr << "Something went wrong on Surface->Texture Conversion" << endl;
		return nullptr;
	}

	return Texture;
}