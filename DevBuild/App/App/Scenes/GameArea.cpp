#include "GameArea.h"

#include "../ArksEngine.h"
#include "../GameManager.h"

namespace ArksEngineComponents
{
	class HealthBarUI;
}

GameArea::GameArea(Game* pOwner)
	: Scene(pOwner)
	, m_pGame(pOwner)

{
}



void GameArea::Enter()
{
	// Call once at program start to seed randomness
	srand(static_cast<unsigned>(time(nullptr)));


	LoadEntity("GameBackground.xml"); // Create our game obj from a xml file

	LoadEntity("Hero.xml"); // Create our player obj from a xml file
	ArksEngine::GameObject* hero = GetEntityManager()->GetGameObject("Hero");

	ArksEngine::GameObject r;

	m_pGame->GetGameManager()->SetPlayer(hero);
	m_pGame->GetGameManager()->SetEntityManager(GetEntityManager());
	hero->GetComponent<ArksEngineComponents::ColliderComponent>().SetCallback([this, hero](ArksEngine::GameObject* pTarget) {

		hero->GetComponent<ArksEngineComponents::HealthComponent>().damage(10);
		SpawnEnemyOutsideScreen(pTarget);
		
		});


	LoadEntity("Enemy.xml"); // Create our enemy obj from a xml file
	ArksEngine::GameObject* enemy = GetEntityManager()->GetGameObject("Enemy");
	enemy->AddComponent<ArksEngineComponents::AiControllerComponent>(GetOwner(), 20.0f);
	enemy->GetComponent<ArksEngineComponents::AiControllerComponent>().SetTarget(GetEntityManager()->GetGameObject("Hero"));
	enemy->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, enemy, hero]() -> void
		{
			if (hero->GetComponent<ArksEngineComponents::HealthComponent>().isDead())
			{
				GetOwner()->GetDebug_Log()->Log("Player is dead");
				return;
			}

			SpawnEnemyOutsideScreen(enemy);
			m_pGame->GetGameManager()->AddScore(250);
		});


	LoadEntity("Enemy2.xml"); // Create our enemy obj from a xml file
	ArksEngine::GameObject* enemy2 = GetEntityManager()->GetGameObject("Enemy2");
	enemy2->AddComponent<ArksEngineComponents::AiControllerComponent>(GetOwner(), 20.0f);
	enemy2->GetComponent<ArksEngineComponents::AiControllerComponent>().SetTarget(GetEntityManager()->GetGameObject("Hero"));
	enemy2->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, enemy2, hero]() -> void
		{

			if (hero->GetComponent<ArksEngineComponents::HealthComponent>().isDead())
			{
				GetOwner()->GetDebug_Log()->Log("Player is dead");
				return;
			}
			
			SpawnEnemyOutsideScreen(enemy2);
			m_pGame->GetGameManager()->AddScore(250);
		});


	LoadEntity("Enemy3.xml"); // Create our enemy obj from a xml file
	ArksEngine::GameObject* enemy3 = GetEntityManager()->GetGameObject("Enemy3");
	enemy3->AddComponent<ArksEngineComponents::AiControllerComponent>(GetOwner(), 20.0f);
	enemy3->GetComponent<ArksEngineComponents::AiControllerComponent>().SetTarget(GetEntityManager()->GetGameObject("Hero"));
	enemy3->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, enemy3, hero]() -> void
		{
			if (hero->GetComponent<ArksEngineComponents::HealthComponent>().isDead())
			{
				GetOwner()->GetDebug_Log()->Log("Player is dead");
				return;
			}

			SpawnEnemyOutsideScreen(enemy3);
			m_pGame->GetGameManager()->AddScore(250);
		});

	LoadEntity("Hud.xml"); // Create our enemy obj from a xml file
	ArksEngine::GameObject* hud = GetEntityManager()->GetGameObject("Hud");
	m_pGame->GetGameManager()->SetHud(hud);

	// Pause Menu
	LoadEntity("PauseMenuBackGround.xml"); // Create our enemy obj from a xml file

	LoadEntity("ContinueButtonPauseMenu.xml"); // Create our enemy obj from a xml file)
	ArksEngine::GameObject* continueBttn = GetEntityManager()->GetGameObject("ContinueButton");
	continueBttn->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			m_pGame->GetGameManager()->UnpauseGame();
		});

	LoadEntity("QuitButtonPauseMenu.xml"); // Create our enemy obj from a xml file
	ArksEngine::GameObject* quitBttn = GetEntityManager()->GetGameObject("QuitButton");
	quitBttn->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			m_pGame->GetGameManager()->ResetPause();
			m_pGame->LoadScene(Game::Test);
		});
	

}

void GameArea::Exit()
{
	Scene::Exit();
}

void GameArea::SpawnEnemyOutsideScreen(const ArksEngine::GameObject* enemy) const
{

	int x, y;

	// Decide random side of the screen for spawn location
	int side = rand() % 4;
	switch (side)
	{
	case 0:  // Left side
		x = -50;
		y = rand() % GetOwner()->GetWindow()->GetScreenHeight();
		break;
	case 1:  // Right side
		x = GetOwner()->GetWindow()->GetScreenWidth() + 50;
		y = rand() % GetOwner()->GetWindow()->GetScreenHeight();
		break;
	case 2:  // Top side
		x = rand() % GetOwner()->GetWindow()->GetScreenWidth();
		y = -50;
		break;
	case 3:  // Bottom side
		x = rand() % GetOwner()->GetWindow()->GetScreenWidth();
		y = GetOwner()->GetWindow()->GetScreenHeight() + 50;
		break;
	}

	// Set position
	enemy->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(x, y);
}


