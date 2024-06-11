#include "EventCenter.h"

EventCenter* EventCenter::sInstance = nullptr;

EventCenter* EventCenter::CreateInstance()
{
	if (sInstance != nullptr)
		return sInstance;
	else
		sInstance = new EventCenter();

	return sInstance;
}

// =============== Void Event ===============
void EventCenter::SubscribeEvent(EmptyEventCallback callback, void* instance)
{
	if (numCallbacks < maxCallbacks)
	{
		callbacks[numCallbacks++] = { callback, instance };
	}
}
void EventCenter::UnsubscribeEvent(EmptyEventCallback callback, void* instance)
{
	for (int i = 0; i < numCallbacks; ++i)
	{
		if (callbacks[i].callback == callback && callbacks[i].instance == instance)
		{
			// Remove the callback by shifting remaining elements
			for (int j = i; j < numCallbacks - 1; ++j)
			{
				callbacks[j] = callbacks[j + 1];
			}
			--numCallbacks;
			return;
		}
	}
}
void EventCenter::PostEvent()
{
	for (int i = 0; i < numCallbacks; ++i)
	{
		callbacks[i].callback(callbacks[i].instance);
	}
}

// =============== Projectile Spawn Event ===============
void EventCenter::SubscribeProjectileEvent(ProjectileEventCallback callback, void* instance)
{
	if (numProjectileCallbacks < maxCallbacks)
	{
		projectileCallbacks[numProjectileCallbacks++] = { callback, instance };
	}
}
void EventCenter::UnsubscribeProjectileEvent(ProjectileEventCallback callback, void* instance)
{
	for (int i = 0; i < numProjectileCallbacks; ++i)
	{
		if (projectileCallbacks[i].callback == callback && projectileCallbacks[i].instance == instance)
		{
			// Remove the callback by shifting remaining elements
			for (int j = i; j < numProjectileCallbacks - 1; ++j)
			{
				projectileCallbacks[j] = projectileCallbacks[j + 1];
			}
			--numProjectileCallbacks;
			return;
		}
	}
}
void EventCenter::PostProjectileEvent(const Vector2f& position, const Vector2f& direction,
	const float& speed, const int& damage, EntityType shooterType)
{
	for (int i = 0; i < numProjectileCallbacks; ++i)
	{
		projectileCallbacks[i].callback(projectileCallbacks[i].instance, 
			position, direction, speed, damage, shooterType);
	}
}

// =============== Collision Event ===============
void EventCenter::SubscribeCollisionEvent(CollisionEventCallback callback, void* instance) 
{
	if (numCollisionCallbacks < maxCallbacks)
	{
		collisionCallbacks[numCollisionCallbacks++] = { callback, instance };
	}
}
void EventCenter::UnsubscribeCollisionEvent(CollisionEventCallback callback, void* instance) 
{
	for (int i = 0; i < numCollisionCallbacks; ++i)
	{
 		if (collisionCallbacks[i].callback == callback && collisionCallbacks[i].instance == instance)
		{
			// Remove the callback by shifting remaining elements
			for (int j = i; j < numCollisionCallbacks - 1; ++j)
			{
				collisionCallbacks[j] = collisionCallbacks[j + 1];
			}
			--numCollisionCallbacks;
			return;
		}
	}
}
void EventCenter::PostCollisionEvent(const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
{
	for (int i = 0; i < numCollisionCallbacks; ++i)
	{
		collisionCallbacks[i].callback(collisionCallbacks[i].instance, colliderID, collidedType, currentType);
	}
}

// =============== Enemy Spawn Event ===============
void EventCenter::SubscribeEnemySpawnEvent(EnemySpawnEventCallback callback, void* instance)
{
	if (numEnemySpawnCallbacks < maxCallbacks)
	{
		enemySpawnCallbacks[numEnemySpawnCallbacks++] = { callback, instance };
	}
}
void EventCenter::UnsubscribeEnemySpawnEvent(EnemySpawnEventCallback callback, void* instance)
{
	for (int i = 0; i < numEnemySpawnCallbacks; ++i)
	{
		if (enemySpawnCallbacks[i].callback == callback && enemySpawnCallbacks[i].instance == instance)
		{
			// Remove the callback by shifting remaining elements
			for (int j = i; j < numEnemySpawnCallbacks - 1; ++j)
			{
				enemySpawnCallbacks[j] = enemySpawnCallbacks[j + 1];
			}
			--numEnemySpawnCallbacks;
			return;
		}
	}
}
void EventCenter::PostEnemySpawnEvent(const int& count, const Vector2f pos, const float& rot, EntityType type)
{
	for (int i = 0; i < numEnemySpawnCallbacks; ++i)
	{
		enemySpawnCallbacks[i].callback(enemySpawnCallbacks[i].instance, count, pos, rot, type);
	}
}

// =============== Score Event ===============
void EventCenter::SubscribeScoreEvent(ScoreEventCallback callback, void* instance) 
{
	if (numScoreCallbacks < maxCallbacks)
	{
		scoreCallbacks[numScoreCallbacks++] = { callback, instance };
	}
}
void EventCenter::UnsubscribeScoreEvent(ScoreEventCallback callback, void* instance) 
{
	for (int i = 0; i < numScoreCallbacks; ++i)
	{
		if (scoreCallbacks[i].callback == callback && scoreCallbacks[i].instance == instance)
		{
			// Remove the callback by shifting remaining elements
			for (int j = i; j < numScoreCallbacks - 1; ++j)
			{
				scoreCallbacks[j] = scoreCallbacks[j + 1];
			}
			--numScoreCallbacks;
			return;
		}
	}
}
void EventCenter::PostScoreEvent(const int& score, EntityType killedType) 
{
	for (int i = 0; i < numScoreCallbacks; ++i)
	{
		scoreCallbacks[i].callback(scoreCallbacks[i].instance, score, killedType);
	}
}

// =============== Health Event ===============
void EventCenter::SubscribeHealthEvent(HealthEventCallback callback, void* instance) 
{
	if (numHealthCallbacks < maxCallbacks)
	{
		healthCallbacks[numHealthCallbacks++] = { callback, instance };
	}
}

void EventCenter::UnsubscribeHealthEvent(HealthEventCallback callback, void* instance) 
{
	for (int i = 0; i < numHealthCallbacks; ++i)
	{
		if (healthCallbacks[i].callback == callback && healthCallbacks[i].instance == instance)
		{
			// Remove the callback by shifting remaining elements
			for (int j = i; j < numHealthCallbacks - 1; ++j)
			{
				healthCallbacks[j] = healthCallbacks[j + 1];
			}
			--numHealthCallbacks;
			return;
		}
	}
}

void EventCenter::PostHealthEvent(const int& health) 
{
	for (int i = 0; i < numHealthCallbacks; ++i)
	{
		healthCallbacks[i].callback(healthCallbacks[i].instance, health);
	}
}

// =============== Bonus Event ===============
void EventCenter::SubscribeBonusEvent(BonusEventCallback callback, void* instance)
{
	if (numBonusCallbacks < maxCallbacks)
	{
		bonusCallbacks[numBonusCallbacks++] = { callback, instance };
	}
}
void EventCenter::UnsubscribeBonusEvent(BonusEventCallback callback, void* instance) 
{
	for (int i = 0; i < numBonusCallbacks; ++i)
	{
		if (bonusCallbacks[i].callback == callback && bonusCallbacks[i].instance == instance)
		{
			// Remove the callback by shifting remaining elements
			for (int j = i; j < numBonusCallbacks - 1; ++j)
			{
				bonusCallbacks[j] = bonusCallbacks[j + 1];
			}
			--numBonusCallbacks;
			return;
		}
	}
}
void EventCenter::PostBonusEvent() 
{
	for (int i = 0; i < numBonusCallbacks; ++i)
	{
		bonusCallbacks[i].callback(bonusCallbacks[i].instance);
	}
}
