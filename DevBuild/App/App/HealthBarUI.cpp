#include "HealthBarUI.h"
#include "ArksEngine.h"

ArksEngineComponents::HealthBarUI::HealthBarUI(ArksEngine::Core* pOwner, ArksEngine::GameObject* pTarget)
	:m_pOwner(pOwner)
	, m_pTarget(pTarget)
	
{
}

void ArksEngineComponents::HealthBarUI::Init()
{
	// Create The Health bar current hp text
	m_pHealthBarCurrentText = new ArksEngine::GameObject;
	m_pHealthBarCurrentText->AddComponent<ArksEngineComponents::TransformComponent>();
	m_pHealthBarCurrentText->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(.9 * 32, .3 * 32);
	m_pHealthBarCurrentText->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(10, 10);
	m_pHealthBarCurrentText->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, "Assets/comicbd.ttf", 20, "na");

	// Create the bar tray
	m_pHealthBarTray = new ArksEngine::GameObject;
	m_pHealthBarCurrentText->AddComponent<ArksEngineComponents::TransformComponent>();
	m_pHealthBarCurrentText->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(2 * 32, .3 * 32);
	m_pHealthBarCurrentText->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(300, 32);
	m_pHealthBarCurrentText->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "HealthTray.png");
	m_pHealthBarCurrentText->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(255, 255, 255);

	// Create the bar
	m_pHealthBarFill = new ArksEngine::GameObject;
	m_pHealthBarFill->AddComponent<ArksEngineComponents::TransformComponent>();
	m_pHealthBarFill->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(2.15 * 32, .42 * 32);
	m_pHealthBarFill->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(290, 22);
	m_pHealthBarFill->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "HealthBar.png");
	m_pHealthBarFill->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(255, 255, 255);

	// Create the max hp text
	m_pHealthBarMaxText = new ArksEngine::GameObject;
	m_pHealthBarMaxText->AddComponent<ArksEngineComponents::TransformComponent>();
	m_pHealthBarMaxText->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(12 * 32, .3 * 32);
	m_pHealthBarMaxText->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(10, 10);
	m_pHealthBarMaxText->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, "Assets/comicbd.ttf", 20, "na");

}

void ArksEngineComponents::HealthBarUI::Update(double deltaTime)
{
	// Convert the current HP to an integer, then to a string to avoid decimal points
	const std::string currentHpStr = std::to_string(static_cast<int>(m_pTarget->GetComponent<HealthComponent>().getHp()));
	const char* currentHp = currentHpStr.c_str();
	// Update the health bar text
	m_pHealthBarCurrentText->GetComponent<ArksEngineComponents::TextUiComponent>().SetText(currentHp);

	// Convert the max HP to an integer, then to a string to avoid decimal points
	const std::string maxHpStr = std::to_string(static_cast<int>(m_pTarget->GetComponent<HealthComponent>().getMaxHp()));
	const char* pmaxHp = maxHpStr.c_str();
	m_pHealthBarMaxText->GetComponent<ArksEngineComponents::TextUiComponent>().SetText(pmaxHp);

	// Update the health bar fill
	float maxHp = m_pTarget->GetComponent<HealthComponent>().getMaxHp();
	float currentHpValue = m_pTarget->GetComponent<HealthComponent>().getHp();

	// Calculate the fill width based on current HP
	float fillWidth = (currentHpValue / maxHp) * 290.0f; // 290 is the max width of the fill
	m_pHealthBarFill->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(fillWidth, 22);
}

void ArksEngineComponents::HealthBarUI::Render(float xOffset)
{
	m_pHealthBarCurrentText->Render(xOffset);
	m_pHealthBarTray->Render(xOffset);
	m_pHealthBarFill->Render(xOffset);
	m_pHealthBarMaxText->Render(xOffset);
}
