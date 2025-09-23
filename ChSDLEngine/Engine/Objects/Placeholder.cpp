#include "Placeholder.h"



Placeholder::Placeholder(float ppm) {
	PPM = ppm;
}

Placeholder::~Placeholder() {

}

void Placeholder::Move(float DeltaTime)
{
	b2Vec2 impulse{ InputDir.x * MoveSpeed, InputDir.y * MoveSpeed };

	if (b2LengthSquared(impulse) > 0) {
		
		b2Body_ApplyLinearImpulseToCenter(BodyInsId, impulse, true);
	}

	b2Vec2 pos = b2Body_GetPosition(BodyInsId);

	Position.x = pos.x * PPM - plchDsT.w / 2;
	Position.y = pos.y * PPM - plchDsT.h / 2;

}

void Placeholder::SetTexture(SDL_Texture* _texture) {

	Texture = _texture;

	SDL_QueryTexture(Texture, nullptr, nullptr, &plchDsT.w, &plchDsT.h);
}