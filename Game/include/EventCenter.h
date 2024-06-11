#pragma once

////////////////////////////////////////////////////////////
// This files is a event dispatcher.
// It is used to send events to all subscribers.
////////////////////////////////////////////////////////////

#include "Event.h"

class EventCenter 
{
private:
	static EventCenter* sInstance;

	int numCallbacks { 0 };
	int numProjectileCallbacks{ 0 };
	int numCollisionCallbacks{ 0 };
	int numEnemySpawnCallbacks{ 0 };
	int numScoreCallbacks{ 0 };
	int numHealthCallbacks{ 0 };
	int numBonusCallbacks{ 0 };

	EmptyEventInfo callbacks[maxCallbacks] = {};
	ProjectileEventInfo projectileCallbacks[maxCallbacks] = {};
	CollisionEventInfo collisionCallbacks[maxCallbacks] = {};
	EnemySpawnEventInfo enemySpawnCallbacks[maxCallbacks] = {};
	ScoreEventInfo scoreCallbacks[maxCallbacks] = {};
	HealthEventInfo healthCallbacks[maxCallbacks] = {};
	BonusEventInfo bonusCallbacks[maxCallbacks] = {};

public:
	static EventCenter* CreateInstance();
	static EventCenter* GetInstance() { return sInstance; };

	void SubscribeEvent(EmptyEventCallback callback, void* instance);
	void UnsubscribeEvent(EmptyEventCallback callback, void* instance);
	void PostEvent();

	void SubscribeProjectileEvent(ProjectileEventCallback callback, void* instance);
	void UnsubscribeProjectileEvent(ProjectileEventCallback callback, void* instance);
	void PostProjectileEvent(const Vector2f& position, const Vector2f& direction,
		const float& speed, const int& damage, EntityType shooterType);

	void SubscribeCollisionEvent(CollisionEventCallback callback, void* instance);
	void UnsubscribeCollisionEvent(CollisionEventCallback callback, void* instance);
	void PostCollisionEvent(const ComponentID& colliderID, EntityType collidedType, EntityType currentType);

	void SubscribeEnemySpawnEvent(EnemySpawnEventCallback callback, void* instance);
	void UnsubscribeEnemySpawnEvent(EnemySpawnEventCallback callback, void* instance);
	void PostEnemySpawnEvent(const int& count, const Vector2f pos, const float& rot, EntityType type);

	void SubscribeScoreEvent(ScoreEventCallback callback, void* instance);
	void UnsubscribeScoreEvent(ScoreEventCallback callback, void* instance);
	void PostScoreEvent(const int& score, EntityType killedType);

	void SubscribeHealthEvent(HealthEventCallback callback, void* instance);
	void UnsubscribeHealthEvent(HealthEventCallback callback, void* instance);
	void PostHealthEvent(const int& hp);

	void SubscribeBonusEvent(BonusEventCallback callback, void* instance);
	void UnsubscribeBonusEvent(BonusEventCallback callback, void* instance);
	void PostBonusEvent();
};