#include "ControllerComponent.h"

#include "PhysicsComponent.h"
#include "../Input.h"
#include "../GameObject.h"

ArksEngineComponents::ControllerComponent::ControllerComponent(ArksEngine::Input* pInput)
	:m_pInput(pInput)
	,m_pPhysics(nullptr)
{
}

void ArksEngineComponents::ControllerComponent::Update(double deltaTime)
{
	
	Process();
}

void ArksEngineComponents::ControllerComponent::Init()
{
	m_pPhysics = &mGameObj->GetComponent<ArksEngineComponents::PhysicsComponent>();
}

void ArksEngineComponents::ControllerComponent::Process() const
{
	if (m_pInput->GetTwoKeysPressed(ArksEngine::Input::KeyCode_A, ArksEngine::Input::KeyCode_S))
		m_pPhysics->SetDirection(-1, 1);
	else if (m_pInput->GetTwoKeysPressed(ArksEngine::Input::KeyCode_A, ArksEngine::Input::KeyCode_W))
		m_pPhysics->SetDirection(-1, -1);
	else if (m_pInput->GetTwoKeysPressed(ArksEngine::Input::KeyCode_D, ArksEngine::Input::KeyCode_S))
		m_pPhysics->SetDirection(1, 1);
	else if (m_pInput->GetTwoKeysPressed(ArksEngine::Input::KeyCode_D, ArksEngine::Input::KeyCode_W))
		m_pPhysics->SetDirection(1, -1);
	else if(m_pInput->GetKeyPressed(ArksEngine::Input::KeyCode_A))
		m_pPhysics->SetDirection(-1, 0);
	else if(m_pInput->GetKeyPressed(ArksEngine::Input::KeyCode_D))
		m_pPhysics->SetDirection(1, 0);
	else if (m_pInput->GetKeyPressed(ArksEngine::Input::KeyCode_W))
		m_pPhysics->SetDirection(0, -1);
	else if (m_pInput->GetKeyPressed(ArksEngine::Input::KeyCode_S))
		m_pPhysics->SetDirection(0, 1);
	else
		m_pPhysics->SetDirection(0, 0);
}
