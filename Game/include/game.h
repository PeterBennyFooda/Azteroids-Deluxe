#include "IGame.h"
#include "EntityFactory.h"

class CGame : public IGame
{
private:
	static const char8_t mGameTitle[20];
	EntityFactory* mEntityFactory;

	const int maxAsteroidSpawnCount = 9;

	int currentAsteroidCount = 0;
	int currentAsteroidSpawnCount = 4;
	int currentBonusScore = 10000;
	int currentScore = 0;
	bool isSpawningSaucer = false;
	bool isAlwaysSpawnSaucer = false;
	bool isSpawningAsteroid = false;

public:
	CGame();
	~CGame();

	bool Initialize(GL_Window* window, Keys* keys);
	void Deinitialize();

	const char8_t *GetGameTitle(){return mGameTitle;}
	uint32_t GetScreenWidth() { return 1024; }
	uint32_t GetScreenHeight() { return 768; }
	uint32_t GetBitsPerPixel() { return 32; }

	void DrawScene();
	void UpdateFrame(uint32_t milliseconds);
	void DestroyGame();

private:
	void clearStage();
	void restartGame();
	void startGame();
	void spawnTitleEnemies();
	void spawnEnemies();
	void windowKeyCheck();

	void onScoreChange(const int& score, EntityType killedType);
	static void onScoreChangeEvent(void* p, const int& score, EntityType killedType);

	void onHealthChange(const int& health);
	static void onHealthChangeEvent(void* p, const int& health);

	void onCollision(const ComponentID& colliderID, EntityType collidedType, EntityType currentType);
	static void onCollisionCallback(void* p, const ComponentID& colliderID, EntityType collidedType, EntityType currentType);
};