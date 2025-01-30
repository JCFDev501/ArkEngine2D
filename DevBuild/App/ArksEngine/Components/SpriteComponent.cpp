#include "SpriteComponent.h"

#include <SDL_render.h>
#include <SDL_timer.h>

#include "ControllerComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../Texture.h"
#include "../Core.h"


ArksEngineComponents::SpriteComponent::SpriteComponent(ArksEngine::Core* pRenderer)
	:m_pTexture(nullptr)
	,m_pTransform(nullptr)
	,m_pPhysics(nullptr)
	,m_pRenderer(pRenderer)
{
}

ArksEngineComponents::SpriteComponent::SpriteComponent(ArksEngine::Core* pRenderer, const char* path)
	:m_pTexture(nullptr)
	,m_pTransform(nullptr)
	,m_pPhysics(nullptr)
	,m_pRenderer(pRenderer)
	,m_pPath(path)
{
}

ArksEngineComponents::SpriteComponent::SpriteComponent(ArksEngine::Core* pRenderer, const char* path,
	int numOfFrames, int speed)
	:m_pTexture(nullptr)
	,m_pTransform(nullptr)
	,m_pRenderer(pRenderer)
	,m_pPath(path)
	,mAnimated(true)
	,mFrames(numOfFrames)
	,mSpeed(speed)
{
}

void ArksEngineComponents::SpriteComponent::Init()
{
	if (m_pPath != nullptr)
	{
		m_pTexture = new ArksEngine::Texture(m_pRenderer, m_pPath);
	}
	
	m_pTransform = &mGameObj->GetComponent<TransformComponent>();

	mSource = { 0, 0 };
	
}

void ArksEngineComponents::SpriteComponent::AddTexture(const std::string& key, const char* path)
{
	if (!m_pTexture)
	{
		mTextures[key] = new ArksEngine::Texture(m_pRenderer, path);
		m_pTexture = mTextures[key];
	}
	else
	{
		mTextures[key] = new ArksEngine::Texture(m_pRenderer, path);
	}
}

void ArksEngineComponents::SpriteComponent::SwitchTexture(const std::string& key)
{
	if (m_pTexture == mTextures[key])
	{
		return;
	}

	m_pTexture = mTextures[key];
}

void ArksEngineComponents::SpriteComponent::SetTextureColor(uint8_t r, uint8_t g, uint8_t b)
{
	if (m_pTexture)
	{
		m_textureColor = { r, g, b };

		// Use SDL_SetTextureColorMod with standard uint8_t types
		SDL_SetTextureColorMod(m_pTexture->GetSDLTexture(), m_textureColor.m_r, m_textureColor.m_g, m_textureColor.m_b);
	}
}

void ArksEngineComponents::SpriteComponent::Update(double deltaTime)
{
	if (mAnimated)
	{
		m_pPhysics = &mGameObj->GetComponent<ArksEngineComponents::PhysicsComponent>();
		if (mGameObj->GetTag() == "Player")
			AnimationManager();
		else
			mSource.m_x = m_pTransform->GetScale().m_x * static_cast<float> (static_cast<int>((SDL_GetTicks() / mSpeed) % mFrames));
	}

		
}

void ArksEngineComponents::SpriteComponent::Render(float xOffset)
{
	if(mAnimated)
	{
		Vector2F newPosition = { m_pTransform->GetPosition().m_x, m_pTransform->GetPosition().m_y };
		newPosition.m_x += xOffset;
		m_pTexture->RenderTexture(mSource, newPosition, m_pTransform->GetScale());
	}
	else
	{
		Vector2F newPosition = { m_pTransform->GetPosition().m_x, m_pTransform->GetPosition().m_y };
		newPosition.m_x += xOffset;
		m_pTexture->RenderTexture(newPosition, m_pTransform->GetScale());
	}
}

void ArksEngineComponents::SpriteComponent::AnimationManager()
{
	if (m_pPhysics->GetFront())
	{
		if (m_pPhysics->GetDirection().m_x == -1 && m_pPhysics->GetDirection().m_y == 1)
			mSource.m_y = 64 * 1;
		else if (m_pPhysics->GetDirection().m_x == -1 && m_pPhysics->GetDirection().m_y == 0)
			mSource.m_y = 64 * 2;
		else if (m_pPhysics->GetDirection().m_x == 1 && m_pPhysics->GetDirection().m_y == 1)
			mSource.m_y = 64 * 7;
		else if (m_pPhysics->GetDirection().m_x == 1 && m_pPhysics->GetDirection().m_y == 0)
			mSource.m_y = 64 * 6;
		else if (m_pPhysics->GetDirection().m_x == 0 && m_pPhysics->GetDirection().m_y == 1)
			mSource.m_y = 64 * 8;
		else
			mSource.m_y = 64 * 0;
	}
	else if (!m_pPhysics->GetFront())
	{
		if (m_pPhysics->GetDirection().m_x == 0 && m_pPhysics->GetDirection().m_y == -1)
			mSource.m_y = 64 * 3;
		else if (m_pPhysics->GetDirection().m_x == 1 && m_pPhysics->GetDirection().m_y == -1)
			mSource.m_y = 64 * 5;
		else if (m_pPhysics->GetDirection().m_x == -1 && m_pPhysics->GetDirection().m_y == -1)
			mSource.m_y = 64 * 9;
		else
			mSource.m_y = 64 * 4;
	}
	

	mSource.m_x = m_pTransform->GetScale().m_x * static_cast<float> (static_cast<int>((SDL_GetTicks() / mSpeed) % mFrames));

}

	
