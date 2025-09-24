#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_set>


struct sAnimationClip {
	SDL_Texture* tex{};
	std::vector<SDL_Rect> frames;

	//Just for Animation purposes
	float animFPS{ 12.f };
};

class AnimatedSprite
{
public:
	void SetClip(const sAnimationClip* c) { clip = c; };
	void Play();
	void Pause();
	void Update(float dt);
	void Draw(class RenderQueue& RQ, int z);

	float x = 0, y = 0;


private:
	const sAnimationClip* clip;
	int FrameIndex = 0;
	float time = 0;

	bool playing = true;
};
 
class AnimationSystem
{
public:
	void Add(AnimatedSprite* s) { list.insert(s); };
	void Remove(AnimatedSprite* s) { list.erase(s); }

	void Update(float dTime) {
		for (auto* sprt : list) {

			sprt->Update(dTime);
	
		}
	}


private:
	std::unordered_set<AnimatedSprite*> list;
};