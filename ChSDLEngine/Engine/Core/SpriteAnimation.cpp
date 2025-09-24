#include "SpriteAnimation.h"
#include "RenderQueue.h"


void AnimatedSprite::Update(float dTime) {

	if (!playing || !clip || clip->frames.empty()) return;

	time += dTime;
	const float frameDur = 1.0f / clip->animFPS;

	while (time >= frameDur) {
		time -= frameDur;
		FrameIndex = (FrameIndex + 1) % (int)clip->frames.size();
	}
}

void AnimatedSprite::Draw(RenderQueue& rq, int z) {

	if (!clip) return;

	SDL_Rect dst =
	{
	static_cast<int> (x),
	static_cast<int> (y),

	clip->frames[0].w,
	clip->frames[0].h
	};

	rq.Add({clip->tex, dst, clip->frames[FrameIndex]});
}