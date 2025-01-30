#pragma once
#include <cstdint>  // For uint8_t
#include <string>
#include <unordered_map>

#include "Component.h"
#include "../Utillities/Vector2.h"

struct SDL_Texture;

struct TextureColor
{
	uint8_t m_r = 255;
	uint8_t m_g = 255;
	uint8_t m_b = 255;
};

namespace ArksEngine
{
	class Core;
	class Texture;
}

namespace ArksEngineComponents
{
	class PhysicsComponent;
	class TransformComponent;

	class SpriteComponent : public Component
	{
		ArksEngine::Texture* m_pTexture;
		std::unordered_map<std::string, ArksEngine::Texture*> mTextures;
		ArksEngineComponents::TransformComponent* m_pTransform;
		ArksEngineComponents::PhysicsComponent* m_pPhysics;
		ArksEngine::Core* m_pRenderer;
		const char* m_pPath;
		Vector2<float> mSource;

		TextureColor m_textureColor;

		// Animation
		bool mAnimated = false;
		int mFrames = 0;
		int mSpeed = 100; // Delay between frames in mili sec
	public:

		SpriteComponent(ArksEngine::Core* pRenderer);
		SpriteComponent(ArksEngine::Core* pRenderer, const char* path);
		SpriteComponent(ArksEngine::Core* pRenderer, const char* path, int numOfFrames, int speed);

		void Init() override;

		void AddTexture(const std::string& key, const char* path);

		// Method to switch the active texture
		void SwitchTexture(const std::string& key);

		void SetTextureColor(uint8_t r, uint8_t g, uint8_t b);

		void Update(double deltaTime) override;

		void Render(float xOffset) override;

		ArksEngine::Texture* GetTexture() const { return m_pTexture; }

		TextureColor GetTextureColor() const { return m_textureColor; }
	private:
		void AnimationManager();
	};
}


