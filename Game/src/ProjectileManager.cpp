#include "ProjectileManager.h"

ProjectileManager* ProjectileManager::sInstance = nullptr;

ProjectileManager* ProjectileManager::CreateInstance()
{
	if (sInstance != nullptr)
		return sInstance;
	else
		sInstance = new ProjectileManager();

	return sInstance;
}

void ProjectileManager::Init(EntityFactory* mFactory)
{
	factory = mFactory;

	EventCenter::GetInstance()->SubscribeProjectileEvent(onProjectileSpawn, this);
}

void ProjectileManager::Shutdown() 
{
	factory = nullptr;

	EventCenter::GetInstance()->UnsubscribeProjectileEvent(onProjectileSpawn, this);
}

void ProjectileManager::SpawnProjectile(const Vector2f& position, const Vector2f& direction, 
	const float& speed, const int& damage, EntityType shooterType)
{
	switch (shooterType) 
	{
		case EntityType::Player:
			factory->CreateProjectile(position, direction, speed, damage, EntityType::Bullet);
			break;
		default:
			factory->CreateProjectile(position, direction, speed, damage, EntityType::EnemyBullet);
			break;
	}
}

void ProjectileManager::onProjectileSpawn(void* p, const Vector2f& position, const Vector2f& direction,
	const float& speed, const int& damage, EntityType shooterType)
{
	((ProjectileManager*)p)->SpawnProjectile(position, direction, speed, damage, shooterType);
}