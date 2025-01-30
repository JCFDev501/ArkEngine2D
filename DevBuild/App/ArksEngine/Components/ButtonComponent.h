#pragma once
#include <chrono>
#include <functional>

#include "Component.h"
#include "SpriteComponent.h"


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

		bool m_ClickAndDragEnable = false;

		// Member variables
		std::chrono::steady_clock::time_point m_lastClickTime;  // Tracks the initial click time
		std::chrono::steady_clock::time_point m_lastTriggerTime; // Tracks the last trigger time for continuous triggers
		const std::chrono::milliseconds m_triggerDelay{ 500 };    // Delay before continuous triggers
		const std::chrono::milliseconds m_triggerInterval{ 10 };  // Interval for continuous triggers

	public:
		ButtonComponent(ArksEngine::Core* pOwner);

		void SetButtonHoverColor(uint8_t r, uint8_t g, uint8_t b);

		bool IsHovering() const { return m_wasHovered; }

		bool GetClickAndDragEnabled() const { return m_ClickAndDragEnable; }

		void SetClickAndDragEnabled(bool val) { m_ClickAndDragEnable = val; }

		// Returns whether (x,y) is within the bounds of the button.
		bool HitTest(int x, int y) const;

	private:
		

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


