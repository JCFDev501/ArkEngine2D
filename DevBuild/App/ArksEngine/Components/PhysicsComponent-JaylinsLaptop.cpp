#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "../Core.h"
#include "../Event.h"
#include "../EventManager.h"
#include "../Utillities/Debug_Log.h"
#include "../Utillities/Vector2.h"
#include "../GameObject.h"

ArksEngineComponents::PhysicsComponent::PhysicsComponent(ArksEngine::Core* pOwner)
	:mSpeed(0)
	,mDirection({ 0,0 })
	,m_pOwner(pOwner)
{
}

void ArksEngineComponents::PhysicsComponent::SetDirection(float x, float y)
{
	mDirection.m_x = x;
	mDirection.m_y = y;
}

void ArksEngineComponents::PhysicsComponent::Update(double deltaTime)
{

	Move(deltaTime);
	
}


void ArksEngineComponents::PhysicsComponent::Init()
{
	m_pTransform = &mGameObj->GetComponent<TransformComponent>();
	mDirection = { 0, 0 };
	mSpeed = 0;
	mNewPos = m_pTransform->GetPosition();

	m_pOwner->GetEventManager()->Add_Listener("Static Collision", [this](const ArksEngine::Event& event)
	{
		EventHandler(event);
	}, 1);

}

void ArksEngineComponents::PhysicsComponent::EventHandler(const ArksEngine::Event& event)
{
	const ArksEngine::GameObject* pGameObject = nullptr;

	// Get the event arguments
	const auto& args = event.GetArgs();

	// Check if there's at least one argument
	if (!args.empty())
	{
		// Try to cast the first argument to GameObject*
		try
		{
			pGameObject = std::any_cast<ArksEngine::GameObject*>(args[0]);
		}
		catch (const std::bad_any_cast& e)
		{
			// Log the error
			m_pOwner->GetDebug_Log()->Error("Bad caste");
		}
	}

	if (mGameObj == pGameObject)
	{
		Vector2F position = { m_pTransform->GetPosition().m_x, m_pTransform->GetPosition().m_y };
		Vector2F deltaPosition = { static_cast<float>(mDirection.m_x), static_cast<float>(mDirection.m_y) };

		m_pOwner->GetDebug_Log()->Log("Collision Detected");

		// Check if the object is moving horizontally (left or right)
		if (mDirection.m_y == 0)
		{
			deltaPosition.m_x += mDirection.m_x < 0 ? -1.0f : 1.0f;
		}
		// Check if the object is moving vertically (up or down)
		else if (mDirection.m_x == 0)
		{
			deltaPosition.m_y += mDirection.m_y < 0 ? -1.0f : 1.0f;
		}

		mFront = (mDirection.m_x >= 0 && mDirection.m_y >= 0) || (mDirection.m_x < 0 && mDirection.m_y > 0);

		mNewPos = { position.m_x - deltaPosition.m_x, position.m_y - deltaPosition.m_y };

		// Move the object slightly out of collision
		const float collisionOffset = -2.f;
		mNewPos = { mNewPos.m_x + (deltaPosition.m_x * collisionOffset), mNewPos.m_y + (deltaPosition.m_y * collisionOffset) };

		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
}
	

void ArksEngineComponents::PhysicsComponent::Move(double deltaTime)
{
	const double deltaPosition = mSpeed * deltaTime;

	Vector2F position = { m_pTransform->GetPosition().m_x, m_pTransform->GetPosition().m_y };
	

	if (mDirection.m_x == -1 && mDirection.m_y == 0)
	{
		mFront = true;
		mNewPos = { position.m_x -= static_cast<float>(deltaPosition), position.m_y };
	}
	else if (mDirection.m_x == 1 && mDirection.m_y == 0)
	{
		mFront = true;
		mNewPos = { position.m_x += static_cast<float>(deltaPosition), position.m_y };
	}
	else if (mDirection.m_x == 0 && mDirection.m_y == 1)
	{
		mFront = true;
		mNewPos = { position.m_x, position.m_y += static_cast<float>(deltaPosition) };
	}
	else if (mDirection.m_x == 0 && mDirection.m_y == -1)
	{
		mFront = false;
		mNewPos = { position.m_x, position.m_y -= static_cast<float>(deltaPosition) };
	}
	else if (mDirection.m_x == -1 && mDirection.m_y == -1)
	{
		mFront = false;
		mNewPos = { position.m_x -= static_cast<float>(deltaPosition), position.m_y -= static_cast<float>(deltaPosition) };
	}
	else if (mDirection.m_x == -1 && mDirection.m_y == 1)
	{
		mFront = true;
		mNewPos = { position.m_x -= static_cast<float>(deltaPosition), position.m_y += static_cast<float>(deltaPosition) };
	}
	else if (mDirection.m_x == 1 && mDirection.m_y == -1)
	{
		mFront = false;
		mNewPos = { position.m_x += static_cast<float>(deltaPosition), position.m_y -= static_cast<float>(deltaPosition) };
	}
	else if (mDirection.m_x == 1 && mDirection.m_y == 1)
	{
		mFront = true;
		mNewPos = { position.m_x += static_cast<float>(deltaPosition), position.m_y += static_cast<float>(deltaPosition) };
	}

	m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
}
