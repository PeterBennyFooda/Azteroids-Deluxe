#include <time.h>
#include <math.h>
#include "random.h"
#include "EnemyManager.h"
#include "EventCenter.h"

EnemyManager* EnemyManager::sInstance = nullptr;

EnemyManager* EnemyManager::CreateInstance()
{
	if (sInstance != nullptr)
		return sInstance;
	else
		sInstance = new EnemyManager();

	return sInstance;
}

void EnemyManager::Init(EntityFactory* mFactory, Vector2f* mPlayerPosPtr)
{
	factory = mFactory;
	playerPosPtr = mPlayerPosPtr;
	EventCenter::GetInstance()->SubscribeEnemySpawnEvent(onEnemySpawnEvent, this);
}

void EnemyManager::Shutdown() 
{
	factory = nullptr;
	playerPosPtr = nullptr;
	EventCenter::GetInstance()->UnsubscribeEnemySpawnEvent(onEnemySpawnEvent, this);
}

void EnemyManager::GenerateEnemy(int count, const Vector2f& pos, const float& rotation, EntityType type)
{
	srand((unsigned int)time(NULL));

	RandomDirection randomDir = getRandomDirection();

	for (int i = 0; i < count; ++i)
	{
		Vector2f direction = { randomDir.x, randomDir.y };

		if (type == EntityType::Saucer1 || type == EntityType::Saucer2 
			|| type == EntityType::Diamond || type == EntityType::Triangle)
			factory->CreateEnemy(type, pos, direction, rotation, playerPosPtr);
		else
			factory->CreateEnemy(type, pos, direction, rotation);

		randomDir = getRandomDirection();
	}
}

void EnemyManager::GenerateEnemy(int count, const Vector2f& pos, EntityType type)
{
	srand((unsigned int)time(NULL));

	RandomDirection randomDir = getRandomDirection();

	for (int i = 0; i < count; ++i)
	{
		Vector2f direction = { randomDir.x, randomDir.y };

		if (type == EntityType::Saucer1 || type == EntityType::Saucer2
			|| type == EntityType::Diamond || type == EntityType::Triangle)
			factory->CreateEnemy(type, pos, direction, playerPosPtr);
		else
			factory->CreateEnemy(type, pos, direction);

		randomDir = getRandomDirection();
	}
}

void EnemyManager::GenerateEnemy(int count, const float& rotation, EntityType type)
{
	srand((unsigned int)time(NULL));

	RandomPosition randomPos = getRandomPosition();
	RandomDirection randomDir = getRandomBorderDirection(randomPos.x, randomPos.y);

	for (int i = 0; i < count; ++i)
	{
		Vector2f position = { randomPos.x, randomPos.y };
		Vector2f direction = { randomDir.x, randomDir.y };

		if (type == EntityType::Saucer1 || type == EntityType::Saucer2
			|| type == EntityType::Diamond || type == EntityType::Triangle)
			factory->CreateEnemy(type, position, direction, rotation, playerPosPtr);
		else
			factory->CreateEnemy(type, position, direction, rotation);

		randomPos = getRandomPosition();
		randomDir = getRandomBorderDirection(randomPos.x, randomPos.y);
	}
}

void EnemyManager::GenerateEnemy(int count, EntityType type)
{
	GenerateEnemy(count, 0, type);
}

EnemyManager::RandomPosition EnemyManager::getRandomPosition()
{
	int maxW = (int)ScreenWidth;
	int maxH = (int)ScreenHeight;

	// max value exclusive
	int signX = getRangedRandom(0, 2) == 0 ? -1 : 1;
	int signY = getRangedRandom(0, 2) == 0 ? -1 : 1;

	int whoIsMax = getRangedRandom(0, 2);

	float randomOffsetX = whoIsMax == 0? maxW : (float)getRangedRandom(0, maxW);
	float randomOffsetY = whoIsMax == 1? maxH : (float)getRangedRandom(0, maxH);

	return { randomOffsetX* signX, randomOffsetY* signY };
}

EnemyManager::RandomDirection EnemyManager::getRandomDirection()
{
	float randomDirX = 0;
	float randomDirY = 0;
	double randAngle = getRangedRandom(0.f, 2 * (float)M_PI);

	randomDirX = (float)cos(randAngle);
	randomDirY = (float)sin(randAngle);

	if (randomDirX == 0.0f && randomDirY == 0.0f)
	{
		randomDirX = 1;
		randomDirY = 1;
	}

	return { randomDirX, randomDirY };
}

EnemyManager::RandomDirection EnemyManager::getRandomBorderDirection(float x, float y) 
{
	float maxW = ScreenWidth/2;
	float maxH = ScreenHeight/2;
	float randomDirX = maxW - x;
	float randomDirY = maxH - y;

	float length = (float)sqrt(randomDirX * randomDirX + randomDirY * randomDirY);
	randomDirX /= length;
	randomDirY /= length;

	return { randomDirX, randomDirY };
}

void EnemyManager::onEnemySpawn(const int& count, const Vector2f pos, const float& rot, EntityType type)
{
	GenerateEnemy(count, pos, rot, type);
}

void EnemyManager::onEnemySpawnEvent(void*p, const int& count, const Vector2f pos, const float& rot, EntityType type)
{
	((EnemyManager*)p)->onEnemySpawn(count, pos, rot, type);
}
