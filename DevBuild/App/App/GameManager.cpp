#include "GameManager.h"

#include "HealthBarUI.h"
#include "ScoreUIComponent.h"
#include "../ArksEngine/Input.h"


GameManager::GameManager(Game* pOwner)
	:m_pGame(pOwner)
{

}

void GameManager::Update(double deltaTime)
{

	
    // In your update or input handling function
    if (m_pGame->GetInput()->GetKeyPressed(ArksEngine::Input::KeyCode_Esc))
    {
        if (!m_IsPaused)
        {
            m_pGame->GetDebug_Log()->Log("Pausing game");
            m_pEntityManager->SetGameObjActiveBasedOffTag("Game", false);
            m_pEntityManager->SetGameObjActiveBasedOffTag("Pause Menu", true);

            m_IsPaused = true;
        }
    }

}

void GameManager::SetHud(ArksEngine::GameObject* hud)
{
	m_pHud = hud;
	m_pHud->AddComponent<ArksEngineComponents::HealthBarUI>(m_pGame, m_pPlayer);
	m_pHud->AddComponent<ArksEngineComponents::ScoreUIComponent>(m_pGame, m_Score);
}

void GameManager::AddScore(int score)
{
	m_Score += score;
	m_pHud->GetComponent<ArksEngineComponents::ScoreUIComponent>().SetScore(m_Score);
}

void GameManager::UnpauseGame()
{
	m_pGame->GetDebug_Log()->Log("Unpausing game");
	m_pEntityManager->SetGameObjActiveBasedOffTag("Game", true);
	m_pEntityManager->SetGameObjActiveBasedOffTag("Pause Menu", false);
	m_IsPaused = false;
}

void GameManager::ResetPause()
{
	m_IsPaused = false;
}

