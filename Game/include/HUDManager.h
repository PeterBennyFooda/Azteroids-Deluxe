#pragma once

////////////////////////////////////////////////////////////
// This file handles HUD.
// Including score, titles and other UI.
////////////////////////////////////////////////////////////

#include "gamedefs.h"

class HUDManager
{
private:
	static HUDManager* sInstance;

	const int maxHealth = 10;
	
	int currentScore = 0;
	int currentHealth = 3;
	int currentBonusScore = 10000;

	char pressShiftToStartText[20] 
	{
		'P', 'R', 'E', 'S', 'S', ' ', 
		'S', 'H', 'I', 'F', 'T', ' ', 
		'T', 'O', ' ', 
		'S', 'T', 'A', 'R', 'T' 
	};
	char pressShiftToRestartText[22]
	{
		'P', 'R', 'E', 'S', 'S', ' ',
		'S', 'H', 'I', 'F', 'T', ' ',
		'T', 'O', ' ',
		'R', 'E', 'S', 'T', 'A', 'R', 'T'
	};
	char azteroidsDeluxeText[17] 
	{ 
		'A', 'Z', 'T', 'E', 'R', 'O', 'I', 'D', 'S', ' ', 
		'D', 'E', 'L', 'U', 'X', 'E', ' ' 
	};
	char petariIncText [10] { 'P', 'E', 'T', 'A', 'R', 'I', ' ', 'I', 'N', 'C'};
	char gameOverText[9] { 'G', 'A', 'M', 'E', ' ', 'O', 'V', 'E', 'R'};
	char bonusAtText[8] { 'B', 'O', 'N', 'U', 'S', ' ', 'A', 'T' };
	int bonusNumsText[7] { -1, -1, 1, 0, 0, 0, 0};
	int scoreNumsText[7] { -1, -1, -1, -1, -1, -1, 0 };
	char scoreText[5] { 'S', 'C', 'O', 'R', 'E' };

public:
	static HUDManager* CreateInstance();
	static HUDManager* GetInstance() { return sInstance; };

	void Init();
	void Render();
	void Shutdown();

private:
	void renderTitle();
	void renderGameOver();
	void renderHUD();
	void parseScore();

	void onScoreChange(const int& score, EntityType killedType);
	static void onScoreChangeEvent(void* p, const int& score, EntityType killedType);

	void onHealthChange(const int& health);
	static void onHealthChangeEvent(void* p, const int& health);

	void onBonusChange(void* p);
	static void onBonusChangeEvent(void* p);
};