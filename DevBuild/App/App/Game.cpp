#include "Game.h"

#include "GameManager.h"
#include "../ArksEngine/SceneManager.h"
#include "Scenes/TestArea.h"
#include "Scenes/GameArea.h"

Game::~Game()
{
	delete m_pGameManager;
	m_pGameManager = nullptr;
}

void Game::InitializeApp(const char* name, const char* assetsFileName, int screenWidth, int screenHeight, const char* localizationFile)
{
	ArksEngine_Initialize(name, assetsFileName, screenWidth, screenHeight, localizationFile); // Initialize The engine

	m_pGameManager = new GameManager{ this }; // Create our GameManager

	LoadScene(Test); // Loads out TestScene
}

void Game::Update(double deltaTime)
{
	GetSceneManager()->UpdateCurrentScene(deltaTime);
	m_pGameManager->Update(deltaTime);
}

void Game::DisplayOutput()
{
	if (!GetQuit())
		GetSceneManager()->RenderCurrentScene();
}

void Game::LoadScene(SceneName scene)
{
	switch (scene)
	{
	case Test:
		GetSceneManager()->ChangeScene(new TestArea{ this });
		break;
	case GameLevel:
		GetSceneManager()->ChangeScene(new GameArea{ this });
		break;
	}
}
