#include "ColliderComponent.h"
#include "SDL.h"
#include "../Renderer.h"
#include "../GameObject.h"
#include "TransformComponent.h"

ArksEngineComponents::ColliderComponent::ColliderComponent(ArksEngine::Renderer* pRenderer)
	:m_pRenderer(pRenderer)
{
}

void ArksEngineComponents::ColliderComponent::Init()
{
	m_pCollider = new SDL_Rect{ 0, 0, mWidth, mHeight };
}

void ArksEngineComponents::ColliderComponent::Update(double deltaTime)
{
	m_pTransform = &mGameObj->GetComponent<ArksEngineComponents::TransformComponent>();

	m_pCollider->x = static_cast<int>(m_pTransform->GetPosition().m_x) + mXOffset;
	m_pCollider->y = static_cast<int>(m_pTransform->GetPosition().m_y) + mYOffset;
	m_pCollider->w = mWidth;
	m_pCollider->h = mHeight;
}

void ArksEngineComponents::ColliderComponent::Render(float xOffset)
{
	m_pRenderer->SetRenderDrawColor(255, 0, 0, 255);

	// Apply the xOffset to the x-coordinate of the position.
	int adjustedX = static_cast<int>(m_pCollider->x + xOffset);

	m_pRenderer->DrawRectangle(m_pCollider->w, m_pCollider->h, adjustedX, m_pCollider->y);
}

void ArksEngineComponents::ColliderComponent::SetScale(float x, float y)
{
	mWidth = static_cast<int>(x);
	mHeight = static_cast<int>(y);
}

void ArksEngineComponents::ColliderComponent::ExecuteCallback(ArksEngine::GameObject* pTarget)
{
	if (m_callback != nullptr)
	{
		m_callback(pTarget);
	}
}

