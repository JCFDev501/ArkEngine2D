#include "PhysicsComponent.h"

#include "SpriteComponent.h"
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
	ArksEngine::GameObject* pGameObject = nullptr;
	ArksEngine::GameObject* pOwner = nullptr;

	// Get the event arguments
	const auto& args = event.GetArgs();

	// Check if there's at least one argument
	if (!args.empty())
	{
		// Try to cast the first argument to GameObject*
		try
		{
			pGameObject = std::any_cast<ArksEngine::GameObject*>(args[0]);
			pOwner = std::any_cast<ArksEngine::GameObject*>(args[1]);

		}
		catch (const std::bad_any_cast& e)
		{
			// Log the error
			m_pOwner->GetDebug_Log()->Error("Bad caste");
		}

		if (pOwner != mGameObj)
		{
			return;
		}
	}


	if (pGameObject)
	{
		if (pGameObject->IsActive())
		{
			if (pGameObject->GetTag() == "BigDot")
			{
				if (mGameObj->GetTag() == "Player")
				{
					//m_pOwner->GetDebug_Log()->Log("Item Collision");

					// Trigger the event to make ghost vulnerable
					m_pOwner->GetEventManager()->Trigger_Event("Vulnerable", {});

					pGameObject->Destroy();
				}
				
			}
			else if (pGameObject->GetTag() == "Item")
			{
				if (mGameObj->GetTag() == "Player")
				{
					//m_pOwner->GetDebug_Log()->Log("Item Collision");

					pGameObject->Destroy();
				}
			
			}
		}
		
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
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
	else if (mDirection.m_x == 1 && mDirection.m_y == 0)
	{
		mFront = true;
		mNewPos = { position.m_x += static_cast<float>(deltaPosition), position.m_y };
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
	else if (mDirection.m_x == 0 && mDirection.m_y == 1)
	{
		mFront = true;
		mNewPos = { position.m_x, position.m_y += static_cast<float>(deltaPosition) };
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
	else if (mDirection.m_x == 0 && mDirection.m_y == -1)
	{
		mFront = false;
		mNewPos = { position.m_x, position.m_y -= static_cast<float>(deltaPosition) };
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
	else if (mDirection.m_x == -1 && mDirection.m_y == -1)
	{
		mFront = false;
		mNewPos = { position.m_x -= static_cast<float>(deltaPosition), position.m_y -= static_cast<float>(deltaPosition) };
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
	else if (mDirection.m_x == -1 && mDirection.m_y == 1)
	{
		mFront = true;
		mNewPos = { position.m_x -= static_cast<float>(deltaPosition), position.m_y += static_cast<float>(deltaPosition) };
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
	else if (mDirection.m_x == 1 && mDirection.m_y == -1)
	{
		mFront = false;
		mNewPos = { position.m_x += static_cast<float>(deltaPosition), position.m_y -= static_cast<float>(deltaPosition) };
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
	else if (mDirection.m_x == 1 && mDirection.m_y == 1)
	{
		mFront = true;
		mNewPos = { position.m_x += static_cast<float>(deltaPosition), position.m_y += static_cast<float>(deltaPosition) };
		m_pTransform->SetPosition(mNewPos.m_x, mNewPos.m_y);
	}
}


