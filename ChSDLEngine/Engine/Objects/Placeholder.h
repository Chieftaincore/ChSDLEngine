#pragma once
#include <iostream>
#include <box2d.h>
#include <String>
#include <SDL.h>

//Controlloble Placeholder.
class Placeholder
{
public:
	Placeholder(float ppm);
	~Placeholder();

	void Move(float DeltaTime);
	void SetTexture(SDL_Texture* Texture);


//ENG Vector Ýnformation
public:
	struct Vec2 { float x{ 0.0f }; float y{ 0.0f }; };
	SDL_Texture* Texture = nullptr;

	b2BodyId BodyInsId;

	SDL_Rect plchDsT{ 0,0,0,0 };
	Vec2 Position{ 100.f, 100.f };
	Vec2 Velocity{ 100.f, 100.f };

	float MoveSpeed = 0.2f;
	Vec2 InputDir{ 0.f ,0.f };

private:
	float PPM;
};