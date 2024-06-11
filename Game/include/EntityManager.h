#pragma once

////////////////////////////////////////////////////////////
// This file control the life cycle of all entities.
// It is responsible for creating, updating, rendering and
// destroying entities.
////////////////////////////////////////////////////////////

#include "Components.h"
#include "Entity.h"
#include "EntityContainer.h"
#include "gamedefs.h"

class EntityManager 
{
private:
	static EntityManager* sInstance;

	EntityContainer entities;

public:
	static EntityManager* CreateInstance();
	static EntityManager* GetInstance() { return sInstance; };

	void Update(float mFT);
	void Render();
	void Refresh();
	void Clear();

	PlayerEntity& AddPlayerEntity();
	EnemyEntity& AddEnemyEntity(EntityType type);
	ProjectileEntity& AddProjectileEntity(EntityType type);

	EntityContainer& GetEntities();
	EntityContainer& GetEntitiesByType(EntityType type);
	EntityContainer& GetEntitiesExceptType(EntityType type);
	EntityContainer& GetEntitiesExceptTypes(EntityType type1, EntityType type2);
	EntityContainer& GetEntitiesExceptTypes(EntityType type1, EntityType type2, EntityType type3);
};