#include "EntityManager.h"

EntityManager* EntityManager::sInstance = nullptr;

EntityManager* EntityManager::CreateInstance()
{
	if (sInstance != nullptr)
		return sInstance;
	else
		sInstance = new EntityManager();

	return sInstance;
}

void EntityManager::Update(float mFT) 
{
	for (int i = 0; i < entities.Size(); i++) 
	{
		entities.GetAt(i)->Update(mFT);
	}
}

void EntityManager::Render()
{
	for (int i = 0; i < entities.Size(); i++)
	{
		entities.GetAt(i)->Render();
	}
}

void EntityManager::Refresh()
{
	for (int i = 0; i < entities.Size(); i++)
	{
		BaseEntity* entity = entities.GetAt(i);
		if(!entity->IsAlive())
		{
			entities.RemoveAt(i);
			delete entity;
			i--;
		}
	}
}

void EntityManager::Clear() 
{
	if(entities.Size() <= 0)
		return;

	for (int i = entities.Size()-1; i >=0; i--)
	{
		BaseEntity* entity = entities.GetAt(i);
		entity->Destroy();
		entities.RemoveAt(i);
		delete entity;
	}
}

PlayerEntity& EntityManager::AddPlayerEntity()
{
	PlayerEntity* entity(new PlayerEntity());
	entity->type = EntityType::Player;
	entities.Append(entity);
	return *entity;
}

EnemyEntity& EntityManager::AddEnemyEntity(EntityType type)
{
	EnemyEntity* entity(new EnemyEntity());
	entity->type = type;
	entities.Append(entity);
	return *entity;
}

ProjectileEntity& EntityManager::AddProjectileEntity(EntityType type)
{
	ProjectileEntity* entity(new ProjectileEntity());
	entity->type = type;
	entities.Append(entity);
	return *entity;
}

EntityContainer& EntityManager::GetEntities() { return entities; }

EntityContainer& EntityManager::GetEntitiesByType(EntityType type) 
{
	EntityContainer* container = new EntityContainer();
	for (int i = 0; i < entities.Size(); i++)
	{
		if (entities.GetAt(i)->type == type)
		{
			container->Append(entities.GetAt(i));
		}
	}
	return *container;
}

EntityContainer& EntityManager::GetEntitiesExceptType(EntityType type) 
{
	EntityContainer* container = new EntityContainer();
	for (int i = 0; i < entities.Size(); i++)
	{
		if (entities.GetAt(i)->type != type)
		{
			container->Append(entities.GetAt(i));
		}
	}
	return *container;
}

EntityContainer& EntityManager::GetEntitiesExceptTypes(EntityType type1, EntityType type2) 
{
	EntityContainer* container = new EntityContainer();
	for (int i = 0; i < entities.Size(); i++)
	{
		if (entities.GetAt(i)->type != type1 && entities.GetAt(i)->type != type2)
		{
			container->Append(entities.GetAt(i));
		}
	}
	return *container;
}

EntityContainer& EntityManager::GetEntitiesExceptTypes(EntityType type1, EntityType type2, EntityType type3)
{
	EntityContainer* container = new EntityContainer();
	for (int i = 0; i < entities.Size(); i++)
	{
		if (entities.GetAt(i)->type != type1 && entities.GetAt(i)->type != type2 && entities.GetAt(i)->type != type3)
		{
			container->Append(entities.GetAt(i));
		}
	}
	return *container;
}