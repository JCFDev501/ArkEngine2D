#pragma once
#include "../ArksEngine/Components/Component.h"


namespace ArksEngine
{
	class Core;
	class GameObject;
}


namespace ArksEngineComponents
{
	class ScoreUIComponent : public Component
	{
		ArksEngine::GameObject* m_pDollarSign = nullptr;
		ArksEngine::GameObject* m_pScoreText = nullptr;
		ArksEngine::Core* m_pOwner = nullptr;
		int m_score = 0;

	public:
		ScoreUIComponent(ArksEngine::Core* pOwner, int score);

		void Init() override;

		void Update(double deltaTime) override;

		void Render(float xOffset) override;

		void SetScore(int score) { m_score = score; }

	};
}

