#pragma once
#include <functional>

#include "Components/Component.h"
#include "Components/SpriteComponent.h"


struct ButtonHoverColor
{
	uint8_t m_r = 255;
	uint8_t m_g = 255;
	uint8_t m_b = 255;

	TextureColor m_originalColor;
};

namespace ArksEngine
{
	class Core;
}

namespace ArksEngineComponents
{
	class TransformComponent;
	class SpriteComponent;

	class ButtonComponent : public Component
	{
		ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;
		ArksEngineComponents::SpriteComponent* m_pSpriteRef = nullptr;

		// The function that will execute upon click
		std::function<void()> m_callback;

		ArksEngine::Core* m_pOwner = nullptr;

		bool m_wasLeftClickPressed = false;

		ButtonHoverColor m_buttonHoverColor;

		bool m_wasHovered = false;

		bool m_hasButtonOriginalColor = false;

	public:
		ButtonComponent(ArksEngine::Core* pOwner);

		void SetButtonHoverColor(uint8_t r, uint8_t g, uint8_t b);

	private:
		// Returns whether (x,y) is within the bounds of the button.
		bool HitTest(int x, int y) const;

		void Init() override;

		void Update(double deltaTime) override;

		// Executes the callback
		void Trigger() const;

	public:

		// Assigns a callback function.
		void OnClick(std::function<void()> callback)
		{
			m_callback = callback;
		}
	};
}


