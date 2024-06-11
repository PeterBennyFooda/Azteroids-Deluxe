#pragma once

////////////////////////////////////////////////////////////
// This file defines all the constants used in the game.
// Also contains some commonly used structs and enums.
////////////////////////////////////////////////////////////

#define M_PI 3.14159265358979323846

// Game settings
constexpr float ScreenWidth = 2000.0f;
constexpr float ScreenHeight = 2000.0f;
constexpr float SpawnOffset = 150.0f;

constexpr int MaxScore = 9999999;
constexpr int MaxBonusScore = 9000000;
constexpr int MaxHealth = 10;

// Entity settings
constexpr float PlayerHeight = 60;
constexpr float PlayerWidth = 60;
constexpr int PlayerHealth = 3;
constexpr float PlayerBaseSpeed = 160000.f;
constexpr float PlayerBaseRotationSpeed = 300.f;
constexpr float PlayerSpeedMod = 1.0f;
constexpr float PlayerFireRateMod = 0.2f;
constexpr float PlayerShieldPenalty = 6.f;

constexpr float BulletHeight = 10;
constexpr float BulletWidth = 10;
constexpr float BulletBaseSpeed = 100000.f;
constexpr int BulletDamage = 1;

constexpr int EnemyBaseHealth = 1;
constexpr float EnemyBaseSpeed = 20000.f;
constexpr float EnemyBaseRotationSpeed = 90.f;
constexpr float Saucer1FireRateMod = 1.8f;
constexpr float Saucer2FireRateMod = 0.8f;

constexpr float Asteroid1Height = 200;
constexpr float Asteroid1Width = 200;
constexpr float Asteroid1SpeedMod = 0.5f;
constexpr int Asteroid1Score = 20;

constexpr float Asteroid2Height = 120;
constexpr float Asteroid2Width = 120;
constexpr float Asteroid2SpeedMod = 1.0f;
constexpr int Asteroid2Score = 50;

constexpr float Asteroid3Height = 80;
constexpr float Asteroid3Width = 80;
constexpr float Asteroid3SpeedMod = 2.0f;
constexpr int Asteroid3Score = 100;

constexpr float DeathStarHeight = 200;
constexpr float DeathStarWidth = 200;
constexpr float DeathStarSpeedMod = 1.0f;
constexpr int DeathStarScore = 50;

constexpr float DiamondHeight = 100;
constexpr float DiamondWidth = 100;
constexpr float DiamondSpeedMod = 1.75f;
constexpr int DiamondScore = 100;

constexpr float TriangleHeight = 100;
constexpr float TriangleWidth = 100;
constexpr float TriangleSpeedMod = 2.5f;
constexpr int TriangleScore = 200;

constexpr float Saucer1Height = 60;
constexpr float Saucer1Width = 60;
constexpr float Saucer1SpeedMod = 1.5f;
constexpr int Saucer1Score = 200;

constexpr float Saucer2Height = 40;
constexpr float Saucer2Width = 40;
constexpr float Saucer2SpeedMod = 1.5f;
constexpr int Saucer2Score = 1000;

constexpr int ParticleCount = 6;
constexpr float ParticleBaseSize = 6.f;
constexpr float ParticleBaseSpeed = 400.f;

// Enums
enum EntityType
{
	None,
	Player,
	Asteroid1,
	Asteroid2,
	Asteroid3,
	DeathStar,
	Diamond,
	Triangle,
	Saucer1,
	Saucer2,
	Bullet,
	EnemyBullet
};


// Others
typedef unsigned long long ComponentID;

// color struct
struct EntityColor
{
	int r;
	int g;
	int b;
};


// simple 2D vector struct
struct Vector2f
{
	float x;
	float y;

	Vector2f() :
		x(0),
		y(0)
	{}

	Vector2f(float x, float y) :
		x(x),
		y(y)
	{}
};