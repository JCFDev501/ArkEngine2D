#include "HealthComponent.h"

#include <chrono>
#include <iostream>
#include "../GameObject.h"
#include "../Core.h"
#include "../Utillities/Debug_Log.h"

ArksEngineComponents::HealthComponent::HealthComponent(ArksEngine::Core* pOwner, float max, float min)
	:m_pOwner(pOwner)
	, m_maxHp(max)
	, m_minHp(min)
{
}

void ArksEngineComponents::HealthComponent::Init()
{
	Component::Init();
}

void ArksEngineComponents::HealthComponent::Update(double deltaTime)
{

    // Check if health is at or below the minimum
    if (mHp <= m_minHp)
    {
        mHp = m_minHp;
        mGameObj->SetActive(false);
		m_isDead = true;
    }
}



