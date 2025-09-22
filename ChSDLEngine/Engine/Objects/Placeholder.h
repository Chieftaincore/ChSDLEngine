#pragma once
#include <iostream>
#include <String>
#include <SDL.h>

//Controlloble Placeholder.
class Placeholder
{
public:
	Placeholder();
	~Placeholder();

	void Move(float DeltaTime);

//ENG Vector Ýnformation
public:
	struct Vec2 { float x{ 0.0f }; float y{ 0.0f }; };
	SDL_Texture* Texture = nullptr;

	SDL_Rect plchDsT{ 0,0,0,0 };
	Vec2 Position{ 100.f, 100.f };
	Vec2 Velocity{ 100.f, 100.f };

	float MoveSpeed = 180.f;
	Vec2 InputDir{ 0.f ,0.f };
};