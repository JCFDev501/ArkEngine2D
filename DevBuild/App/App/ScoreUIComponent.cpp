#include "ScoreUIComponent.h"
#include "ArksEngine.h"

ArksEngineComponents::ScoreUIComponent::ScoreUIComponent(ArksEngine::Core* pOwner, int score)
	:m_pOwner(pOwner)
	, m_score(score)
{
}

void ArksEngineComponents::ScoreUIComponent::Init()
{
	// Create the dollar sign
	m_pDollarSign = new ArksEngine::GameObject();
	m_pDollarSign->AddComponent<ArksEngineComponents::TransformComponent>();
	m_pDollarSign->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(26 * 32, .3 * 32);
	m_pDollarSign->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(50, 32);
	m_pDollarSign->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "Money.png");

	// Create the score text
	m_pScoreText = new ArksEngine::GameObject();
	m_pScoreText->AddComponent<ArksEngineComponents::TransformComponent>();
	m_pScoreText->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(28.6 * 32, .3 * 32);
	m_pScoreText->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(10, 10);
	m_pScoreText->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, "Assets/comicbd.ttf", 20, "na");
}

void ArksEngineComponents::ScoreUIComponent::Update(double deltaTime)
{
	// Convert the score to a string to avoid decimal points
	const std::string score = std::to_string(m_score);
	const char* pscore = score.c_str();
	m_pScoreText->GetComponent<ArksEngineComponents::TextUiComponent>().SetText(pscore);
}

void ArksEngineComponents::ScoreUIComponent::Render(float xOffset)
{
	m_pDollarSign->Render(xOffset);
	m_pScoreText->Render(xOffset);
}
