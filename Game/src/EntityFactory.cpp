#include "gamedefs.h"
#include "EntityFactory.h"
#include "EntityManager.h"	

PlayerEntity& EntityFactory::CreatePlayer(const Vector2f& position)
{
	auto& player(EntityManager::GetInstance()->AddPlayerEntity());

	auto* transform(new CTransform(position));
	player.Transform = transform;
	transform->Init();

	long color = getEntityColor(EntityType::Player);
	EntitySize size = getEntitySize(EntityType::Player);
	auto* shape(new CShape2D(transform, size.height, size.width, EntityType::Player, color));
	player.Shape = shape;
	shape->Init();

	auto* particle(new CParticle2D(transform));
	player.Particle = particle;
	particle->Init();

	Vector2f halfSize(size.height / 2, size.width / 2);
	auto* physics(new CPhysics(transform, halfSize, ScreenWidth, ScreenHeight));
	player.Physics = physics;
	physics->Init();

	float speedMod = getEntitySpeedMod(EntityType::Player);
	auto* stat(new CGameStat(PlayerHealth, speedMod));
	player.Stat = stat;
	stat->Init();

	auto* weapon(new CWeapon(transform, PlayerFireRateMod, EntityType::Player));
	player.Weapon = weapon;
	weapon->Init();

	auto* control(new CPlayerControl(PlayerBaseSpeed, transform, physics, stat, weapon, shape, particle));
	player.Control = control;
	control->Init();

	return player;
}

EnemyEntity& EntityFactory::CreateEnemy(EntityType type, const Vector2f& position, const Vector2f& direction,
	const float& rotation, Vector2f* target)
{
	auto& enemy(EntityManager::GetInstance()->AddEnemyEntity(type));

	auto* transform(new CTransform(position, rotation));
	enemy.Transform = transform;
	transform->Init();

	long color = getEntityColor(type);
	EntitySize size = getEntitySize(type);
	auto* shape(new CShape2D(transform, size.height, size.width, type, color));
	enemy.Shape = shape;
	shape->Init();

	auto* particle(new CParticle2D(transform));
	enemy.Particle = particle;
	particle->Init();

	Vector2f halfSize(size.height / 2, size.width / 2);
	auto* physics(new CPhysics(transform, halfSize, ScreenWidth + SpawnOffset, ScreenHeight + SpawnOffset));
	enemy.Physics = physics;
	physics->Init();

	float speedMod = getEntitySpeedMod(type);
	auto* stat(new CGameStat(EnemyBaseHealth, speedMod));
	enemy.Stat = stat;
	stat->Init();

	float fireRateMod = Saucer1FireRateMod;
	if(type == EntityType::Saucer2)
		fireRateMod = Saucer2FireRateMod;
	auto* weapon(new CWeapon(transform, fireRateMod, type));
	enemy.Weapon = weapon;
	weapon->Init();

	auto* control(new CSimpleEnemyControl(EnemyBaseSpeed, direction, transform, physics, stat, particle, weapon, target, type));
	enemy.Control = control;
	control->Init();

	return enemy;
}

EnemyEntity& EntityFactory::CreateEnemy(EntityType type, const Vector2f& position, 
	const Vector2f& direction, const float& rotation)
{
	return CreateEnemy(type, position, direction, rotation, nullptr);
}

EnemyEntity& EntityFactory::CreateEnemy(EntityType type, const Vector2f& position, 
	const Vector2f& direction, Vector2f* target)
{
	return CreateEnemy(type, position, direction, 0.0f, target);
}

EnemyEntity& EntityFactory::CreateEnemy(EntityType type, const Vector2f& position, const Vector2f& direction)
{
	return CreateEnemy(type, position, direction, 0.0f, nullptr);
}

ProjectileEntity& EntityFactory::CreateProjectile(const Vector2f& position, const Vector2f& direction, 
	const float& speed, const int& damage, EntityType type)
{
	auto& projectile(EntityManager::GetInstance()->AddProjectileEntity(type));

	auto* transform(new CTransform(position));
	projectile.Transform = transform;
	transform->Init();

	long color = getEntityColor(type);
	EntitySize size = getEntitySize(type);
	auto* shape(new CShape2D(transform, size.height, size.width, type, color));
	projectile.Shape = shape;
	shape->Init();

	Vector2f halfSize(size.height / 2, size.width / 2);
	auto* physics(new CPhysics(transform, halfSize, ScreenWidth, ScreenHeight));
	projectile.Physics = physics;
	physics->Init();

	auto* stat(new CStat());
	projectile.Stat = stat;
	stat->Init();

	auto* control(new CProjectile(transform, physics, stat, speed, direction, damage));
	projectile.Projectile = control;
	control->Init();

	return projectile;
}

EntityFactory::EntitySize EntityFactory::getEntitySize(EntityType type)
{
	switch (type)
	{
		case EntityType::Player:
			return EntitySize(PlayerWidth, PlayerHeight);
		case EntityType::Bullet:
		case EntityType::EnemyBullet:
			return EntitySize(BulletWidth, BulletHeight);
		case EntityType::Asteroid1:
			return EntitySize(Asteroid1Width, Asteroid1Height);
		case EntityType::Asteroid2:
			return EntitySize(Asteroid2Width, Asteroid2Height);
		case EntityType::Asteroid3:
			return EntitySize(Asteroid3Width, Asteroid3Height);
		case EntityType::Saucer1:
			return EntitySize(Saucer1Width, Saucer1Height);
		case EntityType::Saucer2:
			return EntitySize(Saucer2Width, Saucer2Height);
		case EntityType::DeathStar:
			return EntitySize(DeathStarWidth, DeathStarHeight);
		case EntityType::Diamond:
			return EntitySize(DiamondWidth, DiamondHeight);
		case EntityType::Triangle:
			return EntitySize(TriangleWidth, TriangleHeight);
		default:
			return EntitySize(PlayerWidth, PlayerHeight);
	}
}

float EntityFactory::getEntitySpeedMod(EntityType type)
{
	switch (type)
	{
		case EntityType::Player:
			return PlayerSpeedMod;
		case EntityType::Bullet:
		case EntityType::EnemyBullet:
			return PlayerSpeedMod;
		case EntityType::Asteroid1:
			return Asteroid1SpeedMod;
		case EntityType::Asteroid2:
			return Asteroid2SpeedMod;
		case EntityType::Asteroid3:
			return Asteroid3SpeedMod;
		case EntityType::Saucer1:
			return Saucer1SpeedMod;
		case EntityType::Saucer2:
			return Saucer2SpeedMod;
		case EntityType::DeathStar:
			return DeathStarSpeedMod;
		case EntityType::Diamond:
			return DiamondSpeedMod;
		case EntityType::Triangle:
			return TriangleSpeedMod;
		default:
			return PlayerSpeedMod;
	}
}

long EntityFactory::getEntityColor(EntityType type)
{
	long color = 0;

	switch (type)
	{
		case EntityType::Player:
			color = PlayerColor.b;
			color += PlayerColor.g << 8;
			color += PlayerColor.r << 16;
			break;
		case EntityType::Bullet:
		case EntityType::EnemyBullet:
			color = BulletColor.b;
			color += BulletColor.g << 8;
			color += BulletColor.r << 16;
			break;
		case EntityType::Asteroid1:
		case EntityType::Asteroid2:
		case EntityType::Asteroid3:
			color = Asteriod1Color.b;
			color += Asteriod1Color.g << 8;
			color += Asteriod1Color.r << 16;
			break;
		case EntityType::Saucer1:
		case EntityType::Saucer2:
		case EntityType::DeathStar:
		default:
			color = PlayerColor.b;
			color += PlayerColor.g << 8;
			color += PlayerColor.r << 16;
			break;
	}

	return color;
}
