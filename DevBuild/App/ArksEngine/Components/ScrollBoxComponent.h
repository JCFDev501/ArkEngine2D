#pragma once
#include <vector>

#include "Component.h"


namespace ArksEngine
{
	class Core;
}

namespace ArksEngineComponents
{
	class TransformComponent;

	class ScrollBoxComponent : public Component
	{
		TransformComponent* m_pTransformRef = nullptr;
		ArksEngine::Core* m_pOwner = nullptr;
		std::vector<ArksEngine::GameObject*> m_gameObjects;

		float width = 0;
		float height = 0;

		const float BUTTON_HEIGHT = 100.0f; // Same height as used in button creation

		float totalButtonHeight = 0;


	public:
		ScrollBoxComponent(ArksEngine::Core* pOwner);
		void AddGameObject(ArksEngine::GameObject* pGameObject);
		void Init() override;

		void Update(double deltaTime) override;
		void Render(float xOffset) override;

		void CreateNumAmoutOfButtons(int amount);

		void ProccessInput();
	};
}


