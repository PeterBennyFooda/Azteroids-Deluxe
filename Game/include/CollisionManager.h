#pragma once

////////////////////////////////////////////////////////////
// This file tests for collision between two entities.
// Post event if collision is detected.
////////////////////////////////////////////////////////////

#include "EntityManager.h"

class CollisionManager 
{
private:
	static CollisionManager* sInstance;
	bool isIntersecting(CPhysics* a, CPhysics* b);

public:
	static CollisionManager* CreateInstance();
	static CollisionManager* GetInstance() { return sInstance; };

	void TestAllCollision();
	void TestCollision(BaseEntity* entityA, BaseEntity* entityB);
};