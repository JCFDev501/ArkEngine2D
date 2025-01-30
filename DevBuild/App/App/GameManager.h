#pragma once
#include "Game.h"
#include "ArksEngine.h"

class GameManager
{
	Game* m_pGame = nullptr; // The game we are managing
	ArksEngine::GameObject* m_pPlayer = nullptr; // The player object
	ArksEngine::GameObjectManager* m_pEntityManager = nullptr; // The entity manager
	ArksEngine::GameObject* m_pHud = nullptr; // The HUD object
	int m_Score = 0; // The player's score

	bool m_IsPaused = false; // Is the game paused?

	// Inside your class definition
	bool m_EscKeyReleased = true;  // New flag to track if Esc key has been released

	bool firstTimeBootedUp = true;

	bool m_SamCharacterSelected = false;

	bool m_MaxCharacterSelected = false;



public:
	GameManager(Game* pOwner);
	~GameManager() = default;
	
	void Update(double deltaTime);
	void SetPlayer(ArksEngine::GameObject* player) { m_pPlayer = player; }
	ArksEngine::GameObject* GetPlayer() const { return m_pPlayer; }
	void SetEntityManager(ArksEngine::GameObjectManager* entityManager) { m_pEntityManager = entityManager; }
	void SetHud(ArksEngine::GameObject* hud);
	void AddScore(int score);

	void UnpauseGame();
	void ResetPause();

	void RestartGame();

	bool IsFirstTimeBootedUp() const { return firstTimeBootedUp; }
	void SetFirstTimeBootedUp(bool val) { firstTimeBootedUp = val; }

	bool SamCharacterSelected() const { return m_SamCharacterSelected; }
	bool MaxCharacterSelected() const { return m_MaxCharacterSelected; }
	void SetSamCharacterSelected(bool val) { m_SamCharacterSelected = val; }
	void SetMaxCharacterSelected(bool val) { m_MaxCharacterSelected = val; }

};

