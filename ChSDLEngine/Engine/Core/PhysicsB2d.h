#pragma once
#include <iostream>
#include <box2d.h>
#include <SDL.h>
#include <unordered_map>

constexpr float p_PPM = 100.f;

class PhysicsB2d {

public:

	PhysicsB2d();
	~PhysicsB2d();
	bool Init(float ppm, float Gravity_x, float Gravity_y);
	void Shutdown();
	void Step(float dt);
	bool IsEnabled();

public:
	b2BodyId CreateBox(float px, float py, float w, float h, bool dynamic, float density = 1.f, float restitution = 0.5f);

private:
	//Pixels per Meter
	b2WorldId p_WorldId;
};