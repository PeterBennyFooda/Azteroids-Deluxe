#pragma once

////////////////////////////////////////////////////////////
// This file defines all the components.
// We can extend this list by adding custom components.
// (I wish I could use STL and templates for reusable codes...)
////////////////////////////////////////////////////////////

#include <math.h>
#include "random.h"
#include "openglframework.h"	
#include "baseTypes.h"
#include "gamedefs.h"
#include "ShapeDraw.h"
#include "EventCenter.h"
#include "Sound.h"

/*
 * (0) Component
 * 
 * Base struct of Componenet. A Componenet has its
 * data and logic implemented in it.
 */
struct Component
{
	ComponentID ID;

	Component() 
	{
		static ComponentID counter = 0;
		ID = counter++;
	}

	virtual ~Component()
	{}

	virtual void Init()
	{}
	virtual void Update(float)
	{}
	virtual void Render()
	{}
};

/*
 * (1) CTransform
 *
 * This Component records position, rotation
 * and scale of an entity.
 *
 * We can use this compoenet to grant an entity
 * the basic information to interact with the world
 * and other entities.
 */
struct CTransform : Component
{
	Vector2f Position;
	Vector2f Scale;
	float Rotation;

	CTransform():
		Position({0,0}),
		Scale({1,1}),
		Rotation(0)
	{}

	CTransform(const Vector2f& pos) :
		Position(pos),
		Scale({ 1,1 }),
		Rotation(0)
	{}

	CTransform(const Vector2f& pos, const float& rot) :
		Position(pos),
		Scale({ 1,1 }),
		Rotation(rot)
	{}
};

/*
 * (2) CShape2D
 *
 * This Component records the shape of an entity.
 * We can use this compoenet to give an entity primitive shapes.
 * 
 */
struct CShape2D : Component
{
public:
	bool Visable { true };
	bool IsOutline { false };

private:
	EntityType entityType { EntityType::Asteroid1 };
	CTransform* transform{ nullptr };
	float height;
	float width;
	long color;

public:
	CShape2D() = default;
	CShape2D(CTransform* mTransform, const float& mHeight, const float& mWidth, EntityType type, long color) :
		transform(mTransform),
		height(mHeight),
		width(mWidth),
		entityType(type),
		color(color)
	{}

	void Render() override
	{
		char red = (char)((color >> 16) & 0xFF);
		char green = (char)((color >> 8) & 0xFF);
		char blue = (char)((color >> 0) & 0xFF);

		if (Visable) 
		{
			switch (entityType) 
			{
				case EntityType::Player:
					DrawSpaceShip(transform->Position.x, transform->Position.y, width, height, red, green, blue, transform->Rotation);
					break;
				case EntityType::Asteroid1:
				case EntityType::Asteroid2:
				case EntityType::Asteroid3:
					DrawAsteroid(transform->Position.x, transform->Position.y, width, red, green, blue, transform->Rotation);
					break;
				case EntityType::Saucer1:
				case EntityType::Saucer2:
					DrawSaucer(transform->Position.x, transform->Position.y, width, height, red, green, blue);
					break;
				case EntityType::DeathStar:
					DrawDeathStar(transform->Position.x, transform->Position.y, 
						width, height, red, green, blue, transform->Rotation, 0);
					break;
				case EntityType::Diamond:
					DrawDeathStar(transform->Position.x, transform->Position.y, 
						width, height, red, green, blue, transform->Rotation, 1);
					break;
				case EntityType::Triangle:
					DrawDeathStar(transform->Position.x, transform->Position.y, 
						width, height, red, green, blue, transform->Rotation, 2);
					break;
				default:
					DrawCircle(width, transform->Position.x, transform->Position.y, red, green, blue, true);
					break;
			}
		}		

		if(IsOutline)
			DrawOutline();
	}

	void DrawOutline() 
	{
		char red = (char)((color >> 16) & 0xFF);
		char green = (char)((color >> 8) & 0xFF);
		char blue = (char)((color >> 0) & 0xFF);

		if (entityType == EntityType::Player) 
		{
			DrawShield(transform->Position.x, transform->Position.y, width*2, height*2, red, green, blue);
		}
	}

	void Erase() 
	{
		Visable = false;
	}
};

/*
 * (3) CParticle2D
 *
 * This Component is particle controller.
 *
 * We can use this compoenet to make an entity
 * emit particles.
 */

struct CParticle2D : Component
{
public:
	bool Visable { true };

private:
	CTransform* transform{ nullptr };

	Vector2f startPosition{ 0.f, 0.f };
	Vector2f positionArray[ParticleCount];
	Vector2f directionArray[ParticleCount];
	float timer{ 0.f };
	float duration{ 0.5f };
	bool isEmitting{ false };

public:
	CParticle2D() = default;
	CParticle2D(CTransform* mTransform) :
		transform(mTransform)
	{}

	void Update(float dt) override
	{
		if (isEmitting)
		{
			timer += dt;
			if (timer >= duration)
			{
				isEmitting = false;
				timer = 0.f;
				Visable = false;
			}

			for (int i = 0; i < ParticleCount; i++)
			{
				positionArray[i].x += ParticleBaseSpeed * directionArray[i].x * dt;
				positionArray[i].y += ParticleBaseSpeed * directionArray[i].y * dt;

				if(positionArray[i].x >= ScreenWidth) positionArray[i].x = -ScreenWidth;
				if(positionArray[i].x <= -ScreenWidth) positionArray[i].x = ScreenWidth;
				if(positionArray[i].y >= ScreenHeight) positionArray[i].y = -ScreenHeight;
				if(positionArray[i].y <= -ScreenHeight) positionArray[i].y = ScreenHeight;
			}
		}
	}

	void Render() override
	{
		if (isEmitting)
		{
			for (int i = 0; i < ParticleCount; i++)
			{
				DrawCircle(ParticleBaseSize, positionArray[i].x, positionArray[i].y, (char)255, (char)255, (char)255, true);
			}
		}
	}

	void Emit()
	{
		startPosition = transform->Position;
		for (int i = 0; i < ParticleCount; i++)
		{
			Vector2f offset = getRandomOffset();
			positionArray[i] = startPosition;
			positionArray[i].x += offset.x;
			positionArray[i].y += offset.y;
			directionArray[i] = getRandomDirection();
		}

		isEmitting = true;
	}

	void Erase()
	{
		Visable = false;
	}

private:
	Vector2f getRandomOffset()
	{
		float randomX = getRangedRandom(0.f, 20.f);
		float randomY = getRangedRandom(0.f, 20.f);

		return { randomX, randomY };
	}

	Vector2f getRandomDirection()
	{
		float randomDirX = 0;
		float randomDirY = 0;
		double randAngle = getRangedRandom(0.f, 2 * (float)M_PI);

		randomDirX = (float)cos(randAngle);
		randomDirY = (float)sin(randAngle);

		if (randomDirX == 0 && randomDirY == 0) randomDirX = 1;

		return { randomDirX, randomDirY };
	}
};

/*
 * (4) CStat
 *
 * This Component provides only simple stats.
 *
 * We only care about whether an entity is dead or not.
 */
struct CStat : Component
{
public:
	bool IsDead{ false };
	bool IsInvincible{ false };

public:
	CStat() = default;
};

/*
*  (5) CGameStat
*  This Component provides character stats.
*
*	We can extend CStat to give character a
*	variety of modifications such as Health,
*	SpeedMod, Armor, etc.
*/

struct CGameStat : Component
{
public:
	int Health { 1 };
	int Score{ 1 };
	float SpeedMod{ 1 };
	bool IsDying{ false };
	bool IsDead{ false };
	bool IsInvincible{ false };
	bool BeforeNotInvincible{ false };
	bool CanBeProtected{ false };
	bool CanGiveScore{ true };

private:
	const float baseHitcoolDown = { 0.5f };
	float hitTimer = { 0.f };
	float hitCoolDown = { 2.0f };
	float deathTimer = { 0.f };
	float deathCoolDown = { 1.5f };

public:
	CGameStat() = default;
	CGameStat(const int& mHP, const float& mSpeedMod) :
		Health(mHP),
		SpeedMod(mSpeedMod)
	{}

	void Update(float dt) override
	{
		if (IsInvincible)
		{
			hitTimer += dt;
			if (hitTimer >= hitCoolDown)
			{
				IsInvincible = false;
				BeforeNotInvincible = false;
				hitTimer = 0.f;
			}
			else if (hitTimer >= hitCoolDown / 2) 
			{
				BeforeNotInvincible = true;
			}
		}

		if (IsDying) 
		{
			deathTimer += dt;
			if (deathTimer >= deathCoolDown)
			{
				IsDead = true;
				deathTimer = 0.f;
			}
		}
	}

	void Hit(int damage) 
	{
		if (!IsInvincible && !IsDying && !IsDead)
		{
			Health -= damage;
			IsInvincible = true;

			if (Health <= 0)
			{
				IsDying = true;
			}
		}
	}

	void Heal(int amount) 
	{
		if (!IsInvincible && !IsDying && !IsDead)
		{
			Health += amount;
		}
	}
};

/*
 * (6) CPhysics
 *
 * This Component makes an entity collidable.
 *
 * We can use this compoenet to give an entity a
 * basic collider and moving force based on its velocity.
 */
struct CPhysics : Component
{
public:
	Vector2f HalfSize;
	Vector2f Velocity;
	float BorderWidth, BorderHeight;

private:
	static const int maxCallbacks { 10 };
	int numCallbacks { 0 };
	int numCollisionCallbacks { 0 };

	EmptyEventInfo outOfBoundCallbacks[maxCallbacks];
	CollisionEventInfo collisionCallbacks[maxCallbacks];
	CTransform* transform{ nullptr };

public:
	CPhysics() = default;
	CPhysics(CTransform* mTransform, const Vector2f& mHalfSize, const float mBorderX, const float mBorderY) :
		transform(mTransform),
		HalfSize(mHalfSize),
		Velocity(0, 0),
		BorderWidth(mBorderX),
		BorderHeight(mBorderY)
	{}
	~CPhysics() override
	{
		EventCenter::GetInstance()->UnsubscribeCollisionEvent(onCollisionCallback, this);
	}

	void Init() override
	{
		EventCenter::GetInstance()->SubscribeCollisionEvent(onCollisionCallback, this);
	}

	void Update(float dt) override
	{
		transform->Position.x += Velocity.x * dt;
		transform->Position.y += Velocity.y * dt;

		checkOutOfBound();
	}

	void SubscribeOutOfBoundEvent(EmptyEventCallback callback, void* instance)
	{
		if (numCallbacks < maxCallbacks) 
		{
			outOfBoundCallbacks[numCallbacks++] = {callback, instance};
		}
	}

	void UnsubscribeOutOfBoundEvent(EmptyEventCallback callback, void* instance)
	{
		for (int i = 0; i < numCallbacks; ++i) 
		{
			if (outOfBoundCallbacks[i].callback == callback && outOfBoundCallbacks[i].instance == instance)
			{
				// Remove the callback by shifting remaining elements
				for (int j = i; j < numCallbacks - 1; ++j) 
				{
					outOfBoundCallbacks[j] = outOfBoundCallbacks[j + 1];
				}
				--numCallbacks;
				return;
			}
		}
	}

	void SubscribeCollisionEvent(CollisionEventCallback callback, void* instance)
	{
		if (numCollisionCallbacks < maxCallbacks)
		{
			collisionCallbacks[numCollisionCallbacks++] = { callback, instance };
		}
	}

	void UnsubscribeCollisionEvent(CollisionEventCallback callback, void* instance)
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
				--numCallbacks;
				return;
			}
		}
	}

	float x() const noexcept
	{
		return transform->Position.x;
	}
	float y() const noexcept
	{
		return transform->Position.y;
	}

	float Top() const noexcept
	{
		return y() - HalfSize.y;
	}
	float Bottom() const noexcept
	{
		return y() + HalfSize.y;
	}

	float Left() const noexcept
	{
		return x() - HalfSize.x;
	}
	float Right() const noexcept
	{
		return x() + HalfSize.x;
	}

private:
	void checkOutOfBound() 
	{
		if (transform->Position.x < -BorderWidth + HalfSize.x)
		{
			notifyOutOfBoundEvent();

			transform->Position.x = BorderWidth - HalfSize.x;
			if (Velocity.y > 0 || Velocity.y < 0)
			{
				transform->Position.y = -transform->Position.y;
			}
			
		}
		else if (transform->Position.x > BorderWidth - HalfSize.x)
		{
			notifyOutOfBoundEvent();

			transform->Position.x = -BorderWidth + HalfSize.x;
			if (Velocity.y > 0 || Velocity.y < 0)
			{
				transform->Position.y = -transform->Position.y;
			}
		}

		if (transform->Position.y < -BorderHeight + HalfSize.y)
		{
			notifyOutOfBoundEvent();

			transform->Position.y = BorderHeight - HalfSize.y;
			if (Velocity.x > 0 || Velocity.x < 0)
			{
				transform->Position.x = -transform->Position.x;
			}
		}
		else if (transform->Position.y > BorderHeight - HalfSize.y)
		{
			notifyOutOfBoundEvent();

			transform->Position.y = -BorderHeight + HalfSize.y;
			if (Velocity.x > 0 || Velocity.x < 0)
			{
				transform->Position.x = -transform->Position.x;
			}
		}
	}

	void notifyOutOfBoundEvent()
	{
		for (int i = 0; i < numCallbacks; ++i) 
		{
			outOfBoundCallbacks[i].callback(outOfBoundCallbacks[i].instance);
		}
	}

	void notifyCollisionEvent(const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		for (int i = 0; i < numCollisionCallbacks; ++i)
		{
			collisionCallbacks[i].callback(collisionCallbacks[i].instance, colliderID, collidedType, currentType);
		}
	}

	void onCollision(const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		if (colliderID == ID) 
		{
			notifyCollisionEvent(colliderID, collidedType, currentType);
		}
	}

	static void onCollisionCallback(void* p, const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		((CPhysics*)p)->onCollision(colliderID, collidedType, currentType);
	}
};

/*
 * (7) CWeapon
 *
 * This Component is weapon controller.
 *
 * We can use this compoenet to shoot projectiles.
 */
struct CWeapon : Component
{
public:
	float FireInterval { 1.f };
	float FireMod{ 1.f };
	bool IsShooting{ false };

private:
	EntityType entityType{ EntityType::Asteroid1 };
	CTransform* transform{ nullptr };
	float fireTimer{ 0.f };

	int shootingSound { 0 };

public:
	CWeapon() = default;
	CWeapon(CTransform* mTransform, const float& mFireMod, EntityType type) :
		transform(mTransform),
		FireMod(mFireMod),
		entityType(type)
	{}
	CWeapon(CTransform* mTransform, const float& mFireInterval,
		const float& mFireMod, EntityType type) :
		transform(mTransform),
		FireInterval(mFireInterval),
		FireMod(mFireMod),
		entityType(type)
	{}

	void Init() override
	{
		shootingSound = Sound::LoadSound("asset/fire.wav");
	}

	void Update(float dt) override
	{
		if (!IsShooting)
			return;

		fireTimer += dt;
		if (fireTimer >= FireInterval * FireMod)
		{
			fireTimer = 0.f;
			IsShooting = false;
		}
	}

	void Shoot(Vector2f direction)
	{
		if (!IsShooting)
		{
			IsShooting = true;
			Sound::Playback(shootingSound);

			EventCenter::GetInstance()
				->PostProjectileEvent(transform->Position, direction, BulletBaseSpeed, BulletDamage, entityType);
		}
	}
};

/*
 * (8) CPlayerControl
 *
 * This Component is player controller.
 *
 * We can use this compoenet to make an entity
 * controlled by the player.
 */
struct CPlayerControl : Component 
{
public:
	float PlayerSpeed;
	bool Stop{ false };

	bool isShield{ false };
	bool isShieldOut{ false };
	float shieldDuration{ 12.0f };
	float shieldTimer{ 0.f };

private:
	float slowMod{ 0.5f };
	Vector2f direction { 0, 1 };
	CShape2D* shape{ nullptr };
	CParticle2D* particle{ nullptr };
	CPhysics* physics{ nullptr };
	CTransform* transform{ nullptr };
	CGameStat* stat{ nullptr };
	CWeapon* weapon{ nullptr };

	int deathSound { 0 };
	int thrustSound { 0 };
	int healSound{ 0 };

public:
	CPlayerControl() = default;
	CPlayerControl(const float& mPlayerSpeed, CTransform* mTransform, CPhysics* mPhysics, 
		CGameStat* mStat, CWeapon* mWeapon, CShape2D* mShape, CParticle2D* mParticle) :
		PlayerSpeed(mPlayerSpeed),
		physics(mPhysics),
		transform(mTransform),
		stat(mStat),
		weapon(mWeapon),
		shape(mShape),
		particle(mParticle)
	{}
	~CPlayerControl() override
	{
		physics->UnsubscribeCollisionEvent(onCollisionEvent, this);
		EventCenter::GetInstance()->UnsubscribeBonusEvent(onBonusChangeEvent, this);
	}

	void Init() override
	{
		physics->SubscribeCollisionEvent(onCollisionEvent, this);
		EventCenter::GetInstance()->SubscribeBonusEvent(onBonusChangeEvent, this);

		// your sounds are never unloaded... there should likely be a corresponding Shutdown for these Init

		deathSound = Sound::LoadSound("asset/bangSmall.wav");
		thrustSound = Sound::LoadSound("asset/thrust.wav");
		healSound = Sound::LoadSound("asset/extraShip.wav");
	}

	void Update(float dt) override
	{
		if (stat->IsDead) 
			return;

		if (stat->IsInvincible && !stat->BeforeNotInvincible) 
		{
			shape->Visable = false;
			shape->IsOutline = false;
			isShieldOut = false;

			transform->Position = { 0, 0 };
			transform->Rotation = 0;
			direction = { 0, 1 };
			
			physics->Velocity.x = 0;
			physics->Velocity.y = 0;
			return;
		}
		else
		{
			shape->Visable = true;
		}


		if (isShield && !isShieldOut) 
		{
			shape->IsOutline = true;
		}
		else if (stat->BeforeNotInvincible)
		{
			shape->IsOutline = true;
		}
		else 
		{
			shape->IsOutline = false;
		}

		if (Stop) 
		{
			physics->Velocity.x = 0;
			physics->Velocity.y = 0;
			return;
		}

		keyboardInput(dt);
	}

private:
	Vector2f getDirection(float angle) 
	{
		// Convert the angle from degrees to radians, 0 degrees is up, 90 degrees is right
		float angleInRadians = angle * ((float)M_PI / 180.0f);

		// Calculate the components of the direction vector using trigonometric functions
		float xComponent = -(float)sin(angleInRadians);
		float yComponent = (float)cos(angleInRadians);

		return { xComponent, yComponent };
	}

	float lerp(float a, float b, float f)
	{
		return a * (1.0f - f) + (b * f);
	}

	void keyboardInput(float dt)
	{
		// shield button
		if (g_keys->keyDown[VK_SHIFT])
		{
			if (!isShieldOut) 
			{
				slowMod = 0.5f;
				isShield = true;
				shieldTimer += dt;
			}
			else 
			{
				isShield = false;
				slowMod = 1.f;
			}

			if (shieldTimer >= shieldDuration)
			{
				shieldTimer = 0.f;
				isShieldOut = true;
				isShield = false;
			}
		}
		else
		{
			isShield = false;
			slowMod = 1.f;
		}

		//shoot
		if (g_keys->keyDown[VK_SPACE])
		{
			weapon -> Shoot(direction);
		}

		// rotation 
		if (g_keys->keyDown[VK_LEFT] || g_keys->keyDown[0x41]) // 0x41 is 'A'
		{
			transform->Rotation += PlayerBaseRotationSpeed * stat->SpeedMod * slowMod * dt;
			if(transform->Rotation > 360.f) transform->Rotation = 0.f;
			if(transform->Rotation < 0.0f) transform->Rotation = 360.f;

			direction = getDirection(transform->Rotation);
		}
		else if (g_keys->keyDown[VK_RIGHT] || g_keys->keyDown[0x44]) // 0x44 is 'D'
		{
			transform->Rotation += -PlayerBaseRotationSpeed * stat->SpeedMod * slowMod * dt;
			if (transform->Rotation > 360.f) transform->Rotation = 0.f;
			if (transform->Rotation < 0.0f) transform->Rotation = 360.f;

			direction = getDirection(transform->Rotation);
		}
		else
		{
			Vector2f targetDir = getDirection(transform->Rotation);
			direction.x = lerp(direction.x, targetDir.x, dt * 1.5f);
			direction.y = lerp(direction.y, targetDir.y, dt * 1.5f);
		}

		// thruster 
		if (g_keys->keyDown[VK_UP] || g_keys->keyDown[0x57]) // 0x57 is 'W'
		{
			float currentVelX = physics->Velocity.x;
			float currentVelY = physics->Velocity.y;
			float targetVelX = PlayerSpeed * stat->SpeedMod * slowMod * direction.x * dt;
			float targetVelY = PlayerSpeed * stat->SpeedMod * slowMod * direction.y * dt;

			physics->Velocity.x = lerp(currentVelX, targetVelX, dt * 1.5f);
			physics->Velocity.y = lerp(currentVelY, targetVelY, dt * 1.5f);

			Sound::Playback(thrustSound);
		}
		else
		{
			physics->Velocity.x = lerp(physics->Velocity.x, 0, dt * 1.5f);
			physics->Velocity.y = lerp(physics->Velocity.y, 0, dt * 1.5f);
		}
	}

	void onCollision(const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		if (collidedType != EntityType::Bullet)
		{
			Sound::Playback(deathSound);
			if (isShield) 
			{
				if (direction.x == 0 && direction.y == 0) 
				{
					int sign = getRangedRandom(0, 2);
					sign = sign == 0 ? 1 : -1;
					direction.x = getRangedRandom(0.5f, 1.0f) * sign;

					sign = getRangedRandom(0, 2);
					sign = sign == 0 ? 1 : -1;
					direction.y = getRangedRandom(0.5f, 1.0f) * sign;
				}
				else
				{
					direction.x *= -1;
					direction.y *= -1;
				}

				if (physics->Velocity.x < PlayerSpeed/2 && physics->Velocity.y < PlayerSpeed / 2)
				{
					int sign = getRangedRandom(0, 2);
					sign = sign == 0 ? 1 : -1;
					physics->Velocity.x = PlayerSpeed * stat->SpeedMod * slowMod * direction.x * 0.025f * sign;

					sign = getRangedRandom(0, 2);
					sign = sign == 0 ? 1 : -1;
					physics->Velocity.y = PlayerSpeed * stat->SpeedMod * slowMod * direction.y * 0.025f * sign;
				}
				else 
				{
					physics->Velocity.x *= -1;
					physics->Velocity.y *= -1;
				}

				shieldTimer += PlayerShieldPenalty * 0.025f;
				return;
			}

			if (stat->IsInvincible && !stat->IsDying && !stat->IsDead)
				return;

			particle->Emit();
			stat->Hit(BulletDamage);
			EventCenter::GetInstance()->PostHealthEvent(stat->Health);
		}
	}

	static void onCollisionEvent(void* p, const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		((CPlayerControl*)p)->onCollision(colliderID, collidedType, currentType);
	}

	void onBonusChange(void* p)
	{
		if (stat->Health >0)
		{
			stat->Heal(1);
			EventCenter::GetInstance()->PostHealthEvent(stat->Health);
			Sound::Playback(healSound);
		}
	}

	static void onBonusChangeEvent(void* p)
	{
		((CPlayerControl*)p)->onBonusChange(p);
	}
};

/*
 * (9) CSimpleEnemyControl
 *
 * This Component is enemy controller.
 *
 * Enemies with this componenet have
 * some simple movesets and AI logic.
 */
struct CSimpleEnemyControl : Component 
{
public:
	float Speed {1};
	bool Stop{ false };

private:
	EntityType entityType{ EntityType::Asteroid1 };
	CParticle2D* particle{ nullptr };
	CPhysics* physics{ nullptr };
	CTransform* transform{ nullptr };
	CGameStat* stat{ nullptr };
	CWeapon* weapon{ nullptr };
	Vector2f direction;
	Vector2f* target{ nullptr };
	float rotMod { 1.0f };

	bool specialFlag{ false };
	float specialDuration { 3.0f };
	float specialTimer{ 0.f };

	int deathSoundBig { 0 };
	int deathSoundMedium { 0 };
	int deathSoundSmall { 0 };

public:
	CSimpleEnemyControl() = default;
	CSimpleEnemyControl(const float mEnemySpeed, Vector2f mDirection,
		CTransform* mTransform, CPhysics* mPhysics, CGameStat* mStat, CParticle2D* mParticle, CWeapon* mWeapon,
		EntityType type) :
		physics(mPhysics),
		transform(mTransform),
		stat(mStat),
		Speed(mEnemySpeed),
		direction(mDirection),
		particle(mParticle),
		weapon(mWeapon),
		entityType(type)
	{}
	CSimpleEnemyControl(const float mEnemySpeed, Vector2f mDirection,
		CTransform* mTransform, CPhysics* mPhysics, CGameStat* mStat, 
		CParticle2D* mParticle, CWeapon* mWeapon, Vector2f* mTarget,
		EntityType type) :
		physics(mPhysics),
		transform(mTransform),
		stat(mStat),
		Speed(mEnemySpeed),
		direction(mDirection),
		particle(mParticle),
		weapon(mWeapon),
		target(mTarget),
		entityType(type)
	{}
	~CSimpleEnemyControl() override
	{
		physics->UnsubscribeCollisionEvent(onCollisionCallback, this);
	}

	void Init() override
	{
		physics->SubscribeCollisionEvent(onCollisionCallback, this);
		rotMod = getRangedRandom(0.5f, 2.0f);

		deathSoundBig = Sound::LoadSound("asset/bangLarge.wav");
		deathSoundMedium = Sound::LoadSound("asset/bangMedium.wav");
		deathSoundSmall = Sound::LoadSound("asset/bangSmall.wav");
	}

	void Update(float dt) override
	{
		if (Stop || stat->IsDead)
		{
			physics->Velocity.x = 0;
			physics->Velocity.y = 0;
			return;
		}

		specialTimer += dt;
		if (specialFlag) 
		{
			if (specialTimer >= specialDuration)
			{
				specialFlag = false;
				specialTimer = 0.f;
			}
		}
		else 
		{
			if (specialTimer >= specialDuration)
			{
				specialFlag = true;
				specialTimer = 0.f;
			}
		}

		Fly(dt);
	}

	void Fly(float dt)
	{
		if (transform->Rotation > 360.f) transform->Rotation = 0.f;
		if (transform->Rotation < 0.0f) transform->Rotation = 360.f;

		switch (entityType) 
		{
			case EntityType::Asteroid1:
			case EntityType::Asteroid2:
			case EntityType::Asteroid3:
				asteroidMove(dt);
				break;
			case EntityType::Saucer1:
			case EntityType::Saucer2:
				saucerMove(dt);
				break;
			case EntityType::DeathStar:
				deathStarMove(dt);
				break;
			case EntityType::Diamond:
				diamondMove(dt);
				break;
			case EntityType::Triangle:
				triangleMove(dt);
				break;
			default:
				asteroidMove(dt);
				break;
		}
	}

private:
	void asteroidMove(float dt)
	{
		physics->Velocity.x = Speed * stat->SpeedMod * direction.x * dt;
		physics->Velocity.y = Speed * stat->SpeedMod * direction.y * dt;
		transform->Rotation += EnemyBaseRotationSpeed * dt * rotMod;
	}

	void deathStarMove(float dt)
	{
		physics->Velocity.x = Speed * stat->SpeedMod * direction.x * dt;
		physics->Velocity.y = Speed * stat->SpeedMod * direction.y * dt;
	}

	void diamondMove(float dt)
	{
		Vector2f targetDirection = getTargetDirection(0);
		float targetRotation = getRotation(targetDirection);
		transform->Rotation = lerp(transform->Rotation, targetRotation, dt * 1.5f);
		direction = getDirectionFromRotation(transform->Rotation);

		physics->Velocity.x = Speed * stat->SpeedMod * direction.x * dt;
		physics->Velocity.y = Speed * stat->SpeedMod * direction.y * dt;
	}

	void triangleMove(float dt)
	{
		Vector2f targetDirection = getTargetDirection(0);
		float targetRotation = getRotation(targetDirection);
		transform->Rotation = lerp(transform->Rotation, targetRotation, dt * 1.5f);
		direction = getDirectionFromRotation(transform->Rotation);

		physics->Velocity.x = Speed * stat->SpeedMod * direction.x * dt;
		physics->Velocity.y = Speed * stat->SpeedMod * direction.y * dt;
	}

	void saucerAttack() 
	{
		Vector2f shootDir = { 0, 1 };
		float randomOffset = getRangedRandom(1.0f, 25.0f);
		shootDir = getTargetDirection(randomOffset);

		if (!specialFlag)
		{
			shootDir = direction;
		}
		weapon->Shoot(shootDir);
	}

	void saucerMove(float dt)
	{
		if (!specialFlag)
		{
			physics->Velocity.x = Speed * stat->SpeedMod * direction.x * dt;
			physics->Velocity.y = Speed * stat->SpeedMod * direction.y * dt;
		}
		else
		{
			physics->Velocity.y = 0;
			if(direction.x>0)
				physics->Velocity.x = Speed * stat->SpeedMod  * dt;
			else
				physics->Velocity.x = -Speed * stat->SpeedMod * dt;
		}
		saucerAttack();
	}

	void dyingEffect()
	{
		if (stat->IsDying)
		{
			particle->Emit();
			spawnChildren();
		}
	}

	void playSound() 
	{
		switch (entityType)
		{
			case EntityType::Asteroid1:
				Sound::Playback(deathSoundBig);
				break;
			case EntityType::Asteroid2:
				Sound::Playback(deathSoundMedium);
				break;
			case EntityType::Asteroid3:
				Sound::Playback(deathSoundSmall);
				break;
			case EntityType::Saucer1:
			case EntityType::Saucer2:
			case EntityType::DeathStar:
			case EntityType::Diamond:
			case EntityType::Triangle:
				Sound::Playback(deathSoundSmall);
				break;
			default:
				break;
		}
	}

	void giveScore() 
	{
		if (stat->CanGiveScore) 
		{
			switch (entityType) 
			{
				case EntityType::Asteroid1:
					EventCenter::GetInstance()->PostScoreEvent(Asteroid1Score, entityType);
					break;
				case EntityType::Asteroid2:
					EventCenter::GetInstance()->PostScoreEvent(Asteroid2Score, entityType);
					break;
				case EntityType::Asteroid3:
					EventCenter::GetInstance()->PostScoreEvent(Asteroid3Score, entityType);
					break;
				case EntityType::Saucer1:
					EventCenter::GetInstance()->PostScoreEvent(Saucer1Score, entityType);
					break;
				case EntityType::Saucer2:
					EventCenter::GetInstance()->PostScoreEvent(Saucer2Score, entityType);
					break;
				case EntityType::DeathStar:
					EventCenter::GetInstance()->PostScoreEvent(DeathStarScore, entityType);
					break;
				case EntityType::Diamond:
					EventCenter::GetInstance()->PostScoreEvent(DiamondScore, entityType);
					break;
				case EntityType::Triangle:
					EventCenter::GetInstance()->PostScoreEvent(TriangleScore, entityType);
					break;
				default:
					break;
			}
		}
	}

	void spawnChildren() 
	{
		float childRotation = 0;
		Vector2f childOffset = { 0, 0 }; 
		Vector2f childPos = transform->Position;

		switch (entityType)
		{
			case EntityType::Asteroid1:
				EventCenter::GetInstance()->PostEnemySpawnEvent(2, childPos, childRotation, EntityType::Asteroid2);
				break;
			case EntityType::Asteroid2:
				EventCenter::GetInstance()->PostEnemySpawnEvent(2, childPos, childRotation, EntityType::Asteroid3);
				break;
			case EntityType::DeathStar:
				childRotation = -55;
				childOffset = { -50, 50 };
				childPos = { transform->Position.x + childOffset.x, transform->Position.y + childOffset.y };
				EventCenter::GetInstance()->PostEnemySpawnEvent(1, childPos, childRotation, EntityType::Diamond);

				childRotation = 0;
				childOffset = { 70, 0 };
				childPos = { transform->Position.x + childOffset.x, transform->Position.y + childOffset.y };
				EventCenter::GetInstance()->PostEnemySpawnEvent(1, childPos, childRotation, EntityType::Diamond);

				childRotation = 70;
				childOffset = { -55, -70 };
				childPos = { transform->Position.x + childOffset.x, transform->Position.y + childOffset.y };
				EventCenter::GetInstance()->PostEnemySpawnEvent(1, childPos, childRotation, EntityType::Diamond);
				break;
			case EntityType::Diamond:
				childRotation = transform->Rotation;
				childOffset = { 0, 50 };
				childPos = { transform->Position.x + childOffset.x, transform->Position.y + childOffset.y };
				EventCenter::GetInstance()->PostEnemySpawnEvent(1, childPos, childRotation, EntityType::Triangle);

				childRotation = transform->Rotation + 180;
				childOffset = { 0, -50 };
				childPos = { transform->Position.x + childOffset.x, transform->Position.y + childOffset.y };
				EventCenter::GetInstance()->PostEnemySpawnEvent(1, childPos, childRotation, EntityType::Triangle);
				break;
			default:
				break;
		}
	}

	Vector2f getTargetDirection(float offset)
	{
		if(target == nullptr)
			return { 0, 1 };

		Vector2f direction = { target->x - transform->Position.x, target->y - transform->Position.y };
		direction.x += offset;
		direction.y += offset;
		float length = (float)sqrt(((double)direction.x * (double)direction.x) + ((double)direction.y * (double)direction.y));
		
		if (length != 0)
		{
			float normalX = direction.x / length;
			float normalY = direction.y / length;
			Vector2f directionNormalized(normalX, normalY);
			direction = directionNormalized;
		}
		else
		{
			direction = { 0, 1 };
		}
		return direction;
	}

	float getRotation(Vector2f direction)
	{
		// Calculate the angle in radians using atan2
		float angleRadians = (float)atan2(-direction.x, direction.y);

		// Convert the angle from radians to degrees
		float angleDegrees = (float)fmod((angleRadians * (180.0f / (float)M_PI) + 360.0f), 360.0f);

		return angleDegrees;
	}

	Vector2f getDirectionFromRotation(float angle)
	{
		// Convert the angle from degrees to radians, 0 degrees is up, 90 degrees is right
		float angleInRadians = angle * ((float)M_PI / 180.0f);

		// Calculate the components of the direction vector using trigonometric functions
		float xComponent = -(float)sin(angleInRadians);
		float yComponent = (float)cos(angleInRadians);

		return { xComponent, yComponent };
	}

	float lerp(float a, float b, float f)
	{
		return a * (1.0f - f) + (b * f);
	}

	static void onCollisionCallback(void* p, const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		((CSimpleEnemyControl*)p)->onCollision(colliderID, collidedType, currentType);
	}

	void onCollision(const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		if (collidedType == EntityType::Bullet)
		{
			if (stat->IsInvincible)
				return;

			stat->Hit(BulletDamage);
			if (stat->IsDying)
			{
				dyingEffect();
				giveScore();
				playSound();
			}
		}
		else if (collidedType == EntityType::EnemyBullet || collidedType == EntityType::Player)
		{
			if (stat->IsInvincible)
				return;

			switch (entityType)
			{
				case EntityType::Asteroid1:
				case EntityType::Asteroid2:
				case EntityType::Asteroid3:
				case EntityType::DeathStar:
				case EntityType::Diamond:
				case EntityType::Triangle:
					stat->Hit(BulletDamage);
					if (stat->IsDying) 
					{
						dyingEffect();
						playSound();
					}
					break;
				default:
					break;
			}
		}
	}
};

/*
 * (10) CProjectile
 *
 * This Component is projectile controller.
 *
 * We can use this compoenet to make an entity
 * a projectile.
 */
struct CProjectile : Component 
{
private:
	EntityType type{ EntityType::Bullet };
	CStat* stat{ nullptr };
	CPhysics* physics{ nullptr };
	CTransform* transform{ nullptr };
	Vector2f direction;

public:
	float Speed;
	bool Stop{ false };
	int Damage{ 1 };
	float isDying{ false };
	float deathDuration { 0.6f };
	float deathTimer{ 0.f };

	CProjectile() = default;
	CProjectile(CTransform* mTransform, CPhysics* mPhysics, CStat* mStat,
		const float& mSpeed, const Vector2f mDirection) :
		transform(mTransform),
		physics(mPhysics),
		stat(mStat),
		Speed(mSpeed),
		direction(mDirection)
	{}
	CProjectile(CTransform* mTransform, CPhysics* mPhysics, CStat* mStat,
			const float& mSpeed, const Vector2f mDirection, const int& mDamage) :
		transform(mTransform),
		physics(mPhysics),
		stat(mStat),
		Speed(mSpeed),
		direction(mDirection),
		Damage(mDamage)
	{}

	void Init() override 
	{
		physics->SubscribeOutOfBoundEvent(onDeathCallback, this);
		physics->SubscribeCollisionEvent(onCollisionCallback, this);
	}

	void Update(float dt) override
	{
		if (Stop || stat->IsDead)
		{
			physics->Velocity.x = 0;
			physics->Velocity.y = 0;
			return;
		}

		if (isDying) 
		{
			deathTimer += dt;
			if (deathTimer >= deathDuration)
			{
				stat->IsDead = true;
				deathTimer = 0.f;
			}
		}
		Fly(dt);
	}

	void Fly(float dt)
	{
		physics->Velocity.x = Speed * direction.x * dt;
		physics->Velocity.y = Speed * direction.y * dt;
	}

	void Die()
	{
		isDying = true;
		physics->UnsubscribeOutOfBoundEvent(onDeathCallback, this);
		physics->UnsubscribeCollisionEvent(onCollisionCallback, this);
	}

private:
	static void onDeathCallback(void* p)
	{
		((CProjectile*)p)->Die();
	}

	static void onCollisionCallback(void* p, const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		((CProjectile*)p)->onCollision(colliderID, collidedType, currentType);
	}

	void onCollision(const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
	{
		if (collidedType != EntityType::Player && collidedType != EntityType::Bullet
			&& collidedType != EntityType::EnemyBullet && collidedType != EntityType::Saucer1
			&& collidedType != EntityType::Saucer2)
		{
			stat->IsDead = true;
			Stop = true;
		}
	}
};
