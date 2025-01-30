#pragma once
#include "Component.h"

namespace ArksEngine
{
	class Core;
}

namespace ArksEngineComponents
{
	class TransformComponent;

	class AiControllerComponent : public Component
	{
		ArksEngine::Core* m_pOwner;
		ArksEngine::GameObject* m_pTarget = nullptr;
		float m_speed = 0.0f;
		ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;

	public:
		AiControllerComponent(ArksEngine::Core* pOwner, float speed);

		void Init() override;

		void Update(double deltaTime) override;

		void SetTarget(ArksEngine::GameObject* target) { m_pTarget = target; }
	};
}


