#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "random.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "igame.h"

// My includes
#include "EventCenter.h"
#include "EntityManager.h"
#include "ProjectileManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "HUDManager.h"

IGame* CreateGame() {
	return new CGame();
}

void DestroyGame(IGame* pGame) {
	delete pGame;
}

// Declarations
const char8_t CGame::mGameTitle[]="Framework1";


CGame::CGame() {
	EventCenter::CreateInstance();
	EntityManager::CreateInstance();
	ProjectileManager::CreateInstance();
	EnemyManager::CreateInstance();
	CollisionManager::CreateInstance();
	HUDManager::CreateInstance();

	StateManager::CreateInstance();
}

CGame::~CGame()
{
	delete EventCenter::GetInstance();
	delete EntityManager::GetInstance();
	delete ProjectileManager::GetInstance();
	delete EnemyManager::GetInstance();
	delete CollisionManager::GetInstance();
	delete HUDManager::GetInstance();

	delete StateManager::GetInstance();
}

bool CGame::Initialize (GL_Window* window, Keys* keys)
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	ShowCursor(TRUE);

	// start in title screen
	StateManager::GetInstance()->SetState(StateManager::Title);

	EventCenter::GetInstance()->SubscribeScoreEvent(onScoreChangeEvent, this);
	EventCenter::GetInstance()->SubscribeHealthEvent(onHealthChangeEvent, this);
	EventCenter::GetInstance()->SubscribeCollisionEvent(onCollisionCallback, this);

	// init the entity factory
	mEntityFactory = new EntityFactory();

	// call this at game start to have enemies messing around
	restartGame();

	return true;
}

void CGame::Deinitialize() {
	StateManager::GetInstance()->Shutdown();

	HUDManager::GetInstance()->Shutdown();
	ProjectileManager::GetInstance()->Shutdown();
	EnemyManager::GetInstance()->Shutdown();
	EntityManager::GetInstance()->Clear();

	// unsubscribe events
	EventCenter::GetInstance()->UnsubscribeScoreEvent(onScoreChangeEvent, this);
	EventCenter::GetInstance()->UnsubscribeHealthEvent(onHealthChangeEvent, this);
	EventCenter::GetInstance()->UnsubscribeCollisionEvent(onCollisionCallback, this);
}

void CGame::UpdateFrame(uint32_t milliseconds)			
{
	// deltaTime in seconds
	float deltaTime = (float)(milliseconds) / 1000.0f;

	windowKeyCheck();
	switch (StateManager::GetInstance()->GetState())
	{
		case StateManager::Title:
			if (g_keys->keyDown[VK_SHIFT])
			{
				g_keys->keyDown[VK_SHIFT] = false;
				StateManager::GetInstance()->SetState(StateManager::InGame);
				startGame();
			}
			break;
		case StateManager::InGame:
			if(!isSpawningAsteroid)
				spawnEnemies();
			break;
		case StateManager::GameOver:
			if (g_keys->keyDown[VK_SHIFT])
			{
				g_keys->keyDown[VK_SHIFT] = false;
				restartGame();
			}
			break;
		default:
			break;
	}

	// update all entities and destroy dead ones
	EntityManager::GetInstance()->Refresh();
	EntityManager::GetInstance()->Update(deltaTime);

	// test collisions
	CollisionManager::GetInstance()->TestAllCollision();
}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();

	HUDManager::GetInstance()->Render();
	EntityManager::GetInstance()->Render();
}

// ================ private methods ================
void CGame::clearStage()
{
	ProjectileManager::GetInstance()->Shutdown();
	EnemyManager::GetInstance()->Shutdown();
	HUDManager::GetInstance()->Shutdown();
	EntityManager::GetInstance()->Clear();
}

void CGame::restartGame()
{
	clearStage();

	// Title show witout player
	Vector2f position = Vector2f(0, 0);
	auto& playerPosPtr(position);
	HUDManager::GetInstance()->Init();
	EnemyManager::GetInstance()->Init(mEntityFactory, &playerPosPtr);
	ProjectileManager::GetInstance()->Init(mEntityFactory);
	spawnTitleEnemies();

	StateManager::GetInstance()->SetState(StateManager::Title);
}

void CGame::startGame() 
{
	clearStage();

	// init spawn values
	currentScore = 0;
	currentBonusScore = 10000;
	currentAsteroidSpawnCount = 0;
	currentAsteroidCount = currentAsteroidSpawnCount;
	isSpawningSaucer = false;
	isAlwaysSpawnSaucer = false;
 	isSpawningAsteroid = false;

	// spawn player
	Vector2f position = Vector2f(0, 0);
	auto* playerTransform(mEntityFactory->CreatePlayer(position).Transform);
	auto& playerPosPtr(playerTransform->Position);

	// init managers
	HUDManager::GetInstance()->Init();
	EnemyManager::GetInstance()->Init(mEntityFactory, &playerPosPtr);
	ProjectileManager::GetInstance()->Init(mEntityFactory);
}

void CGame::spawnTitleEnemies() 
{
	// thses are the enemies that will be shown in the title screen
	EnemyManager::GetInstance()->GenerateEnemy(8, EntityType::Asteroid1);
	EnemyManager::GetInstance()->GenerateEnemy(1, {-1000.f, -1000.f }, EntityType::Saucer1);
	EnemyManager::GetInstance()->GenerateEnemy(1, EntityType::Saucer2);
	EnemyManager::GetInstance()->GenerateEnemy(1, -25, EntityType::DeathStar);
}

void CGame::spawnEnemies()
{
	// spawn enemies based on current asteroid count
	// asteroids will be spawned in a range of 4 to 9, increasing by 1 each time
	if (currentAsteroidCount <= 0 && !isSpawningAsteroid)
	{
		isSpawningAsteroid = true;

		// theses are special enemies that will be spawned randomly
		int spawnDeathStar = getRangedRandom(0, 100);
		int spawnSaucer = getRangedRandom(0, 100);

		// generate only large asteroids
		currentAsteroidCount = currentAsteroidSpawnCount;
		EnemyManager::GetInstance()->GenerateEnemy(currentAsteroidSpawnCount, EntityType::Asteroid1);
		currentAsteroidSpawnCount 
			= currentAsteroidSpawnCount < maxAsteroidSpawnCount? currentAsteroidSpawnCount + 1 : maxAsteroidSpawnCount;

		if (isAlwaysSpawnSaucer) // always spawn small saucer if score is greater than 10000
		{
			EnemyManager::GetInstance()->GenerateEnemy(1, EntityType::Saucer2);
		}

		// spawn small saucer and death star randomly
		if (spawnSaucer <= 50)
		{
			EnemyManager::GetInstance()->GenerateEnemy(1, EntityType::Saucer1);
		}
		if (spawnDeathStar <= 25) 
		{
			EnemyManager::GetInstance()->GenerateEnemy(1, EntityType::DeathStar);
		}

		isSpawningAsteroid = false;
	}
}

void CGame::windowKeyCheck() 
{
	if (g_keys->keyDown[VK_ESCAPE])							// Is ESC Being Pressed?
	{
		TerminateApplication(g_window);						// Terminate The Program
	}

	if (g_keys->keyDown[VK_F1])								// Is F1 Being Pressed?
	{
		ToggleFullscreen(g_window);							// Toggle Fullscreen Mode
	}
}

void CGame::onScoreChange(const int& score, EntityType killedType) 
{
	currentScore = currentScore >= MaxScore? MaxScore : currentScore + score;

	// spawn small saucer if score is greater than 10000
	if (currentScore >= 10000 && !isAlwaysSpawnSaucer)
	{
		isAlwaysSpawnSaucer = true;
	}

	// if score is greater than current bonus score, increase player hp by 1
	if (currentScore >= currentBonusScore)
	{
		currentBonusScore = currentBonusScore < MaxBonusScore? currentBonusScore + 10000 : MaxBonusScore;
		EventCenter::GetInstance()->PostBonusEvent();
	}
}
void CGame::onScoreChangeEvent(void* p, const int& score, EntityType killedType) 
{
	((CGame*)p)->onScoreChange(score, killedType);
}
void CGame::onHealthChange(const int& health) 
{
	if (health <= 0) 
	{
		StateManager::GetInstance()->SetState(StateManager::GameOver);
	}
}
void CGame::onHealthChangeEvent(void* p, const int& health) 
{
	((CGame*)p)->onHealthChange(health);
}
void CGame::onCollision(const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
{
	switch (collidedType)
	{
		case EntityType::Asteroid1:
			currentAsteroidCount--;
			if (currentAsteroidCount <= 0)
				currentAsteroidCount = 0;
			break;
		default:
			break;
	}
}

void CGame::onCollisionCallback(void* p, const ComponentID& colliderID, EntityType collidedType, EntityType currentType)
{
	((CGame*)p)->onCollision(colliderID, collidedType, currentType);
}
