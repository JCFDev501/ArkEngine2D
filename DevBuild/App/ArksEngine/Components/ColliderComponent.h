#pragma once
#include <string>

#include "Component.h"
#include <functional>


struct SDL_Rect;


namespace ArksEngine
{
	class Renderer;
}

namespace ArksEngineComponents
{
	class TransformComponent;

	class ColliderComponent : public Component
	{
		SDL_Rect* m_pCollider;
		std::string mTag;
		ArksEngine::Renderer* m_pRenderer;

		int mWidth = 0;
		int mHeight = 0;
		int mXOffset = 0;
		int mYOffset = 0;

		ArksEngineComponents::TransformComponent* m_pTransform;

		// The function that will execute upon click
		std::function<void(ArksEngine::GameObject*)> m_callback;


	public:
		ColliderComponent(ArksEngine::Renderer* pRenderer);

		[[nodiscard]] SDL_Rect* GetCollider() const { return m_pCollider; }

		void Init() override;
		void Update(double deltaTime) override;
		void Render(float xOffset) override;

		void SetWidth(int w) { mWidth = w; }
		void SetHeight(int h) { mHeight = h; }
		void SetXOffset(int x) { mXOffset = x; }
		void SetYOffset(int y) { mYOffset = y; }

		void SetScale(float x, float y);

		// New method to set the callback
		void SetCallback(std::function<void(ArksEngine::GameObject*)> callback) { m_callback = callback; }

		// Method to execute the callback, passing the target GameObject
		void ExecuteCallback(ArksEngine::GameObject* pTarget);

	private:
	};
}

