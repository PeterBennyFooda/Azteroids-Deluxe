#pragma once

////////////////////////////////////////////////////////////
// This file defines all the entities.
// We can extend this list by adding custom entites.
////////////////////////////////////////////////////////////

#include "Components.h"
#include "gamedefs.h"

struct BaseEntity
{
protected:
	bool isAlive { true };
	bool isActive { true };
public:
	CTransform* Transform { nullptr };
	CShape2D* Shape { nullptr };
	CPhysics* Physics{ nullptr };
	EntityType type { EntityType::None };

	virtual ~BaseEntity()
	{}

	virtual void Update(float)
	{}

	virtual void Render()
	{}

	bool IsAlive() const
	{
		return isAlive;
	}

	bool IsActive() const
	{
		return isActive;
	}
	
	void Destroy()
	{
		isAlive = false;
	}
};

struct PlayerEntity : BaseEntity
{
public:
	CPlayerControl* Control { nullptr };
	CGameStat* Stat { nullptr };
	CWeapon* Weapon { nullptr };
	CParticle2D* Particle { nullptr };

	PlayerEntity() = default;
	~PlayerEntity() override
	{
		delete Transform;
		delete Shape;
		delete Physics;
		delete Control;
		delete Stat;
		delete Weapon;
		delete Particle;
	}

    void Update(float dt) override
	{
		if (checkAlive())
		{
			Particle->Update(dt);

			if (!isActive)
				return;

			Stat->Update(dt);
			Control->Update(dt);
			Physics->Update(dt);
			Weapon->Update(dt);
		}
	}

	void Render() override
	{
		Shape->Render();
		Particle->Render();
	}

private:
	bool checkAlive()
	{
		if (Stat->IsDead)
		{
			Particle->Erase();
			Destroy();
			return false;
		}
		else if (Stat->IsDying)
		{
			Shape->Erase();
			isActive = false;
		}
		return true;
	}
};

struct EnemyEntity : BaseEntity
{
public:
	CSimpleEnemyControl* Control { nullptr };
	CGameStat* Stat { nullptr };
	CWeapon* Weapon{ nullptr };
	CParticle2D* Particle{ nullptr };

	EnemyEntity() = default;
	~EnemyEntity() override
	{
		delete Transform;
		delete Shape;
		delete Physics;
		delete Control;
		delete Stat;
		delete Weapon;
		delete Particle;
	}

	void Update(float dt) override
	{
		if (checkAlive())
		{
			Particle->Update(dt);

			if(!isActive)
				return;

			Stat->Update(dt);
			Control->Update(dt);
			Physics->Update(dt);
			Weapon->Update(dt);
		}
	}

	void Render() override
	{
		Shape->Render();
		Particle->Render();
	}

private:
	bool checkAlive()
	{
		if (Stat->IsDead)
		{
			Particle->Erase();
			Destroy();
			return false;
		}
		else if (Stat->IsDying)
		{
			Shape->Erase();
			isActive = false;
		}
		return true;
	}
};

struct ProjectileEntity : BaseEntity
{
public:
	CStat* Stat;
	CProjectile* Projectile { nullptr };

	ProjectileEntity() = default;
	~ProjectileEntity() override
	{
		delete Transform;
		delete Shape;
		delete Physics;
		delete Projectile;
		delete Stat;
	}

	void Update(float dt) override
	{
		if (checkAlive())
		{
			Projectile->Update(dt);
			Physics->Update(dt);
		}
	}

	void Render() override
	{
		Shape->Render();
	}

private:
	bool checkAlive()
	{
		if (Stat->IsDead)
		{
			isActive = false;
			Shape->Erase();
			Destroy();
			return false;
		}
		return true;
	}
};