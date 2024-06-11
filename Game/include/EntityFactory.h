#pragma once

////////////////////////////////////////////////////////////
// This file is a factory for creating entities.
// It is used to create entities with the different parameters.
////////////////////////////////////////////////////////////

#include "Entity.h"
#include "gamedefs.h"

class EntityFactory
{
public:
	struct EntitySize 
	{
		float width;
		float height;

		EntitySize(float width, float height) : width(width), height(height) {}
	};

	PlayerEntity& CreatePlayer(const Vector2f& position);
	EnemyEntity& CreateEnemy(EntityType type, const Vector2f& position, const Vector2f& direction);
	EnemyEntity& CreateEnemy(EntityType type, const Vector2f& position, const Vector2f& direction, const float& rotation);
	EnemyEntity& CreateEnemy(EntityType type, const Vector2f& position, const Vector2f& direction, Vector2f* target);
	EnemyEntity& CreateEnemy(EntityType type, const Vector2f& position, const Vector2f& direction, const float& rotation, Vector2f* target);
	ProjectileEntity& CreateProjectile(const Vector2f& position, const Vector2f& direction, const float& speed, const int& damage, EntityType type);

private:
	EntityColor PlayerColor = { 255, 255, 255 };
	EntityColor BulletColor = { 255, 255, 255 };
	EntityColor Asteriod1Color = { 255, 255, 255 };

	EntitySize getEntitySize(EntityType type);
	float getEntitySpeedMod(EntityType type);
	long getEntityColor(EntityType type);
};
