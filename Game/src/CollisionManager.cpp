#include "CollisionManager.h"
#include "EventCenter.h"

CollisionManager* CollisionManager::sInstance = nullptr;

CollisionManager* CollisionManager::CreateInstance()
{
	if (sInstance != nullptr)
		return sInstance;
	else
		sInstance = new CollisionManager();

	return sInstance;
}

void CollisionManager::TestAllCollision() 
{
	// get list of all different entities
	auto& players(EntityManager::GetInstance()->GetEntitiesByType(EntityType::Player));
	auto& playerProjectiles(EntityManager::GetInstance()->GetEntitiesByType(EntityType::Bullet));
	auto& enemies(EntityManager::GetInstance()->GetEntitiesExceptTypes(EntityType::Player, EntityType::Bullet, EntityType::EnemyBullet));
	auto& enemyProjectiles(EntityManager::GetInstance()->GetEntitiesByType(EntityType::EnemyBullet));

	//Enemies only collide with players.
	for (int i = 0; i < enemies.Size(); ++i)
	{
		auto* e1(enemies.GetAt(i));
		//Check collisions with all players.
		for (int j = 0; j < players.Size(); ++j)
		{
			auto* p(players.GetAt(j));
			TestCollision(e1, p);
		}
	}

	//Enemies Projectiles collide with player.
	for (int i = 0; i < enemyProjectiles.Size(); ++i)
	{
		auto* pj(enemyProjectiles.GetAt(i));
		//Check collisions with all enemies.
		for (int j = 0; j < players.Size(); ++j)
		{
			auto* p(players.GetAt(j));
			TestCollision(pj, p);
		}
	}

	//Enemies Projectiles collide with other enemies.
	for (int i = 0; i < enemyProjectiles.Size(); ++i)
	{
		auto* pj(enemyProjectiles.GetAt(i));
		//Check collisions with all enemies.
		for (int j = 0; j < enemies.Size(); ++j)
		{
			auto* e2(enemies.GetAt(j));
			TestCollision(pj, e2);
		}
	}

	//Player Projectiles only collide with enemies.
	for (int i = 0; i < playerProjectiles.Size(); ++i)
	{
		auto* pj(playerProjectiles.GetAt(i));
		//Check collisions with all enemies.
		for (int j = 0; j < enemies.Size(); ++j)
		{
			auto* e2(enemies.GetAt(j));
			TestCollision(pj, e2);
		}
	}
}

void CollisionManager::TestCollision(BaseEntity* entityA, BaseEntity* entityB) 
{
	// if either entity is not active, don't test collision
	if (!entityA->IsActive() || !entityB->IsActive())
		return;

	auto* colliderA(entityA->Physics);
	auto* colliderB(entityB->Physics);

	if (isIntersecting(colliderA, colliderB))
	{
		EventCenter::GetInstance()->PostCollisionEvent(colliderA->ID, entityB->type, entityA->type);
		EventCenter::GetInstance()->PostCollisionEvent(colliderB->ID, entityA->type, entityB->type);
	}
}

bool CollisionManager::isIntersecting(CPhysics* a, CPhysics* b)
{
	// simple AABB collision detection
	bool isIntersecting 
		= a->Right() >= b->Left() 
		&& a->Left() <= b->Right() 
		&& a->Bottom() >= b->Top() 
		&& a->Top() <= b->Bottom();

	return isIntersecting;
}