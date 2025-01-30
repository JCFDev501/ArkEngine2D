#pragma once
#include "../ArksEngine/Components/Component.h"


namespace ArksEngine
{
	class Core;
	class GameObject;
}


namespace ArksEngineComponents
{
	class HealthBarUI : public Component
	{
		ArksEngine::GameObject* m_pHealthBarTray = nullptr;
		ArksEngine::GameObject* m_pHealthBarFill = nullptr;
		ArksEngine::GameObject* m_pHealthBarMaxText = nullptr;
		ArksEngine::GameObject* m_pHealthBarCurrentText = nullptr;
		ArksEngine::Core* m_pOwner = nullptr;
		ArksEngine::GameObject* m_pTarget;

	public:
		HealthBarUI(ArksEngine::Core* pOwner, ArksEngine::GameObject* pTarget);

		void Init() override;

		void Update(double deltaTime) override;

		void Render(float xOffset) override;

	};
}



