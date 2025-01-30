#include "ToggleBoxComponent.h"

#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"

ArksEngineComponents::ToggleBoxComponent::ToggleBoxComponent(ArksEngine::Core* pOwner, const char* file)
	:m_pOwner(pOwner)
	,m_pFileName(file)
	,mIsToggleLeft(false)
{
}

void ArksEngineComponents::ToggleBoxComponent::Init()
{
	m_pTransformRef = &mGameObj->GetComponent<ArksEngineComponents::TransformComponent>();

	m_pToggleNobe = new ArksEngine::GameObject;
	m_pToggleNobe->AddComponent<ArksEngineComponents::TransformComponent>();

	m_pToggleNobe->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, m_pFileName);
	m_pToggleNobe->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(180, 255, 180);
}

void ArksEngineComponents::ToggleBoxComponent::Update(double deltaTime)
{
	if (!mDid)
	{
		m_pToggleNobe->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(m_pTransformRef->GetPosition().m_x, m_pTransformRef->GetPosition().m_y + 4);
		m_pToggleNobe->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(m_pTransformRef->GetScale().m_x / 2, m_pTransformRef->GetScale().m_y - 10);
		mDid = true;
	}
	

	m_pToggleNobe->Update(deltaTime);

}

void ArksEngineComponents::ToggleBoxComponent::Render(float xOffset)
{
	m_pToggleNobe->Render(xOffset);
}

void ArksEngineComponents::ToggleBoxComponent::Toggle()
{
	float x = m_pToggleNobe->GetComponent<TransformComponent>().GetPosition().m_x;
	float y = m_pToggleNobe->GetComponent<TransformComponent>().GetPosition().m_y;

	if (mIsToggleLeft)
	{
		m_pToggleNobe->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(x - 75, y);
		mIsToggleLeft = false;
	}
	else if (!mIsToggleLeft)
	{
		m_pToggleNobe->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(x + 75, y);
		mIsToggleLeft = true;

	}
}
