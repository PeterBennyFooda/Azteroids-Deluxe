#pragma once

////////////////////////////////////////////////////////////
// This file controls the spawning of projectiles.
////////////////////////////////////////////////////////////

#include "gamedefs.h"
#include "EntityFactory.h"
#include "EventCenter.h"

class ProjectileManager
{
private:
	static ProjectileManager* sInstance;
	EntityFactory* factory;

public:
	static ProjectileManager* CreateInstance();
	static ProjectileManager* GetInstance() { return sInstance; };

	void Init(EntityFactory* mFactory);
	void Shutdown();
	void SpawnProjectile(const Vector2f& position, const Vector2f& direction, 
		const float& speed, const int& damage, EntityType shooterType);

private:
	static void onProjectileSpawn(void* p, const Vector2f& position, const Vector2f& direction,
		const float& speed, const int& damage, EntityType shooterType);
};