#pragma once

////////////////////////////////////////////////////////////
// This file handles enemy spawning.
// There are different ways to spawn enemies.
////////////////////////////////////////////////////////////

#include "gamedefs.h"
#include "EntityFactory.h"

class EnemyManager 
{
private:
	struct RandomPosition
	{
		float x;
		float y;
	};
	struct RandomDirection
	{
		float x;
		float y;
	};

	static EnemyManager* sInstance;

	const float Xmax = ScreenWidth;
	const float Ymax = ScreenHeight;
	EntityFactory* factory { nullptr };
	Vector2f* playerPosPtr { nullptr };

public:
	static EnemyManager* CreateInstance();
	static EnemyManager* GetInstance() { return sInstance; };

	void Init(EntityFactory* mFactorym, Vector2f* playerPosPtr);
	void Shutdown();
	void GenerateEnemy(int count, const Vector2f& pos, const float& rotation, EntityType type);
	void GenerateEnemy(int count, const Vector2f& pos, EntityType type);
	void GenerateEnemy(int count, const float& rotation, EntityType type);
	void GenerateEnemy(int count, EntityType type);

private:
	RandomPosition getRandomPosition();
	RandomDirection getRandomDirection();
	RandomDirection getRandomBorderDirection(float x, float y);

	void onEnemySpawn(const int& count, const Vector2f pos, const float& rot, EntityType type);
	static void onEnemySpawnEvent(void* p, const int& count, const Vector2f pos, const float& rot, EntityType type);
};