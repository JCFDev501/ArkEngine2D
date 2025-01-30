#pragma once
#include "ArksEngine.h"


class GameManager;

class Game : public ArksEngine::Core
{
	GameManager* m_pGameManager = nullptr;

public:

	enum SceneName
	{
		Test,
		GameLevel
	};

	Game() = default;
	~Game();

	void InitializeApp(const char* name, const char* assetsFileName, int screenWidth, int screenHeight, const char* localizationFile = nullptr);

	void Update(double deltaTime) override;

	void DisplayOutput() override;

	void LoadScene(SceneName scene);

	GameManager* GetGameManager() const { return m_pGameManager; }
};

