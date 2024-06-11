#pragma once

////////////////////////////////////////////////////////////
// This file defins events that can be post or listen to.
////////////////////////////////////////////////////////////

#include "gamedefs.h"

static const int maxCallbacks{ 2048 };

typedef void(*EmptyEventCallback)(void*);
struct EmptyEventInfo
{
	EmptyEventCallback callback;
	void* instance;
};

typedef void(*ProjectileEventCallback)(void*, const Vector2f& position, const Vector2f& direction,
	const float& speed, const int& damage, EntityType shooterType);
struct ProjectileEventInfo
{
	ProjectileEventCallback callback;
	void* instance;
};

typedef void(*CollisionEventCallback)(void*, const ComponentID& colliderID, EntityType collidedType, EntityType currentType);
struct CollisionEventInfo
{
	CollisionEventCallback callback;
	void* instance;
};

typedef void(*EnemySpawnEventCallback)(void*, const int& count, const Vector2f pos, const float& rot, EntityType type);
struct EnemySpawnEventInfo
{
	EnemySpawnEventCallback callback;
	void* instance;
};

typedef void(*ScoreEventCallback)(void*, const int& score, EntityType killedType);
struct ScoreEventInfo
{
	ScoreEventCallback callback;
	void* instance;
};

typedef void(*HealthEventCallback)(void*, const int& hp);
struct HealthEventInfo
{
	HealthEventCallback callback;
	void* instance;
};

typedef void(*BonusEventCallback)(void*);
struct BonusEventInfo
{
	BonusEventCallback callback;
	void* instance;
};