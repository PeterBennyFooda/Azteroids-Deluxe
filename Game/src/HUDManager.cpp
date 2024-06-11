#include "HUDManager.h"
#include "baseTypes.h"
#include "ShapeDraw.h"
#include "StateManager.h"
#include "EventCenter.h"

HUDManager* HUDManager::sInstance = nullptr;

HUDManager* HUDManager::CreateInstance()
{
	if (sInstance != nullptr)
		return sInstance;
	else
		sInstance = new HUDManager();

	return sInstance;
}

void HUDManager::Init() 
{
	currentScore = 0;
	currentHealth = 3;
	currentBonusScore = 10000;

	parseScore();

	EventCenter::GetInstance()->SubscribeScoreEvent(onScoreChangeEvent, this);
	EventCenter::GetInstance()->SubscribeHealthEvent(onHealthChangeEvent, this);
}

void HUDManager::Shutdown()
{
	EventCenter::GetInstance()->UnsubscribeScoreEvent(onScoreChangeEvent, this);
	EventCenter::GetInstance()->UnsubscribeHealthEvent(onHealthChangeEvent, this);
}

void HUDManager::Render()
{
	switch (StateManager::GetInstance()->GetState())
	{
		case StateManager::Title:
			renderTitle();
			break;
		case StateManager::InGame:
			renderHUD();
			break;
		case StateManager::GameOver:
			renderGameOver();
			break;
		default:
			break;
	}
}

void HUDManager::renderTitle() 
{
	DrawLetters(-730, 500, (char)255, (char)255, (char)255, azteroidsDeluxeText, 17, 60);
	DrawLetters(-600, 0, (char)255, (char)255, (char)255, pressShiftToStartText, 20, 40);
	DrawLetters(-250, -1000, (char)255, (char)255, (char)255, petariIncText, 10, 30);
}

void HUDManager::renderGameOver() 
{
	DrawLetters(-450, 500, (char)255, (char)255, (char)255, gameOverText, 9, 60);
	DrawLetters(-650, 0, (char)255, (char)255, (char)255, pressShiftToRestartText, 22, 40);

	// score display
	DrawLetters(-425, -500, (char)255, (char)255, (char)255, scoreText, 5, 40);
	DrawNumbers(-50, -500, (char)255, (char)255, (char)255, scoreNumsText, 7, 40);
}

void HUDManager::renderHUD() 
{
	// bonus points display
	DrawLetters(-700, 1500, (char)255, (char)255, (char)255, bonusAtText, 8, 50);
	DrawNumbers(100, 1500, (char)255, (char)255, (char)255, bonusNumsText, 7, 50);

	// score display
	DrawNumbers(-2000, 1800, (char)255, (char)255, (char)255, scoreNumsText, 7, 50);
	
	// health display
	float offset = 0;
	for (int i = 0; i < currentHealth; i++)
	{
		DrawSpaceShip(-1800+offset, 1500, PlayerWidth * 0.8, PlayerHeight * 0.8, (char)255, (char)255, (char)255, 0);
		offset += 150;
	}
}

void HUDManager::parseScore()
{
	int score = currentScore;	
	int digit = -1;

	// parse score into digits
	if (currentScore < 10) 
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i == 6) 
			{
				digit = score % 10;
				scoreNumsText[i] = digit;
				score /= 10;
			}
			else
				scoreNumsText[i] = -1;
		}
	}
	else if (currentScore >= 10 && currentScore < 100) 
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i >= 5)
			{
				digit = score % 10;
				scoreNumsText[i] = digit;
				score /= 10;
			}
			else
				scoreNumsText[i] = -1;
		}
	}
	else if (currentScore >= 100 && currentScore < 1000)
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i >= 4)
			{
				digit = score % 10;
				scoreNumsText[i] = digit;
				score /= 10;
			}
			else
				scoreNumsText[i] = -1;
		}
	}
	else if (currentScore >= 1000 && currentScore < 10000)
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i >= 3)
			{
				digit = score % 10;
				scoreNumsText[i] = digit;
				score /= 10;
			}
			else
				scoreNumsText[i] = -1;
		}
	}
	else if (currentScore >= 10000 && currentScore < 100000)
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i >= 2)
			{
				digit = score % 10;
				scoreNumsText[i] = digit;
				score /= 10;
			}
			else 
				scoreNumsText[i] = -1;
		}
	}
	else if (currentScore >= 100000 && currentScore < 1000000)
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i >= 1)
			{
				digit = score % 10;
				scoreNumsText[i] = digit;
				score /= 10;
			}
			else
				scoreNumsText[i] = -1;
		}
	}
	else
	{
		for (int i = 6; i >=0 ; i--)
		{
			digit = score % 10;
			scoreNumsText[i] = digit;
			score /= 10;
		}
	}

	score = currentBonusScore;
	digit = -1;

	// parse bonus score into digits
	if (currentBonusScore >= 10000 && currentBonusScore < 100000)
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i >= 2)
			{
				digit = score % 10;
				bonusNumsText[i] = digit;
				score /= 10;
			}
			else
				scoreNumsText[i] = -1;
		}
	}
	else if (currentBonusScore >= 100000 && currentBonusScore < 1000000)
	{
		for (int i = 6; i >= 0; i--)
		{
			if (i >= 1)
			{
				digit = score % 10;
				bonusNumsText[i] = digit;
				score /= 10;
			}
			else
				bonusNumsText[i] = -1;
		}
	}
	else
	{
		for (int i = 6; i >= 0; i--)
		{
			digit = score % 10;
			bonusNumsText[i] = digit;
			score /= 10;
		}
	}
}

void HUDManager::onScoreChange(const int& score, EntityType killedType)
{
	currentScore += score;
	if(currentScore >= MaxScore)
		currentScore = MaxScore;

	if (currentScore >= currentBonusScore)
	{
		currentBonusScore = currentBonusScore < MaxBonusScore ? currentBonusScore + 10000 : MaxBonusScore;
	}

	parseScore();
}

void HUDManager::onScoreChangeEvent(void* p, const int& score, EntityType killedType)
{
	((HUDManager*)p)->onScoreChange(score, killedType);
}

void HUDManager::onHealthChange(const int& health)
{
	currentHealth = health;
}

void HUDManager::onHealthChangeEvent(void* p, const int& health)
{
	((HUDManager*)p)->onHealthChange(health);
}

void HUDManager::onBonusChange(void* p)
{
	currentHealth++;
}

void HUDManager::onBonusChangeEvent(void* p)
{
	((HUDManager*)p)->onBonusChange(p);
}