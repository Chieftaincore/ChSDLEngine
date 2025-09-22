#include "Placeholder.h"

Placeholder::Placeholder() {

}

Placeholder::~Placeholder() {

}

void Placeholder::Move(float DeltaTime)
{
	Position.x += InputDir.x * MoveSpeed * DeltaTime;
	Position.y += InputDir.y * MoveSpeed * DeltaTime;
}