#include "PhysicsB2d.h"

PhysicsB2d::PhysicsB2d() {

}

PhysicsB2d::~PhysicsB2d() {

}

bool PhysicsB2d::Init(float ppm, float gravx, float gravy) {

	//Kullanýlmýyorsa kaldýrmayý unutma.
	b2WorldDef WorldDef = b2DefaultWorldDef();

	WorldDef.gravity.x = gravx;
	WorldDef.gravity.y = gravy;

	WorldDef.enableSleep = true;

	p_WorldId = b2CreateWorld(&WorldDef);

	return true;
}

void PhysicsB2d::Shutdown() {

	b2DestroyWorld(p_WorldId);
	p_WorldId = b2_nullWorldId;
}

void PhysicsB2d::Step(float DeltaTime) {

	if (b2World_IsValid(p_WorldId)) return;
	b2World_Step(p_WorldId, 1.0f / 60.f, 4);
}

b2BodyId PhysicsB2d::CreateBox(float px, float py, float w, float h, bool dynamic, float density, float restitution) {

	b2BodyDef def = b2DefaultBodyDef();
	def.type = dynamic ? b2_dynamicBody : b2_staticBody;
	def.position = { 0 / p_PPM, 0 / p_PPM };

	b2BodyId body = b2CreateBody(p_WorldId, &def);

	b2Polygon poly;
	poly = b2MakeBox((100.f / p_PPM), (100.f / p_PPM));

	b2ShapeDef shapedef = b2DefaultShapeDef();
	shapedef.density = density;
	shapedef.material.restitution = restitution;


	b2ShapeId shapeId = b2CreatePolygonShape(body, &shapedef, &poly);

	return body;
	
}