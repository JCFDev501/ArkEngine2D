#pragma once
#include "Component.h"

namespace ArksEngine
{
	class Core;
}

namespace ArksEngineComponents
{
	class TransformComponent;

	class ToggleBoxComponent : public Component
	{
		ArksEngine::GameObject* m_pToggleNobe = nullptr;
		ArksEngine::Core* m_pOwner = nullptr;
		ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;
		const char* m_pFileName = nullptr;

		bool mIsToggleLeft;
		bool mDid = false;
	public:
		ToggleBoxComponent(ArksEngine::Core* pOwner, const char* file);

		void Init() override;
		void Update(double deltaTime) override;
		void Render(float xOffset) override;

		void Toggle();
	};
}


