#pragma once
#include "Component.h"

namespace ArksEngine
{
	class Core;
}

namespace ArksEngineComponents
{
	class TransformComponent;
	class SpriteComponent;

	class SliderComponent : public Component
	{
		ArksEngine::GameObject* m_pKnob = nullptr;
		ArksEngine::Core* m_pOwner = nullptr;
		ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;
		ArksEngineComponents::SpriteComponent* m_pSpriteRef = nullptr;
		const char* m_pFileName = nullptr;
		bool mDid = false;

	public:
		SliderComponent(ArksEngine::Core* pOwner, const char* file);
		void Init() override;
		void Update(double deltaTime) override;
		void Render(float xOffset) override;


	private:
		void OnKnobClicked();

	};
}


