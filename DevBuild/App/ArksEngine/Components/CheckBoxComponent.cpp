#include "CheckBoxComponent.h"

#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"

ArksEngineComponents::CheckBoxComponent::CheckBoxComponent(ArksEngine::Core* pOwner, const char* file)
	:m_pOwner(pOwner)
	,m_pFileName(file)
	,mIsChecked(false)
{
}

void ArksEngineComponents::CheckBoxComponent::Init()
{
	m_pTransformRef = &mGameObj->GetComponent<ArksEngineComponents::TransformComponent>();

	m_pCheckMark = new ArksEngine::GameObject;
	m_pCheckMark->AddComponent<ArksEngineComponents::TransformComponent>();

	m_pCheckMark->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, m_pFileName);
	m_pCheckMark->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(0, 255, 0);
}

void ArksEngineComponents::CheckBoxComponent::Update(double deltaTime)
{
	if (mIsChecked)
	{
		m_pCheckMark->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(m_pTransformRef->GetPosition().m_x, m_pTransformRef->GetPosition().m_y);
		m_pCheckMark->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(m_pTransformRef->GetScale().m_x - 5, m_pTransformRef->GetScale().m_y - 5);

		m_pCheckMark->Update(deltaTime);
	}
	
}

void ArksEngineComponents::CheckBoxComponent::Render(float xOffset)
{

	if (mIsChecked)
	{
		m_pCheckMark->Render(xOffset);
	}
	
}

void ArksEngineComponents::CheckBoxComponent::SetIsChecked()
{
	if (mIsChecked)
	{
		mIsChecked = false;
	}
	else if (!mIsChecked)
	{
		mIsChecked = true;
	}
}
