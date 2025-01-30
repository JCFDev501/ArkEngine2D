#include "SliderComponent.h"

#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
#include "../Input.h"
#include "../Core.h"

ArksEngineComponents::SliderComponent::SliderComponent(ArksEngine::Core* pOwner, const char* file)
	:m_pOwner(pOwner)
	,m_pFileName(file)
{
}

void ArksEngineComponents::SliderComponent::Init()
{
	// Create the knob as a separate game object
	m_pKnob = new ArksEngine::GameObject;
	m_pKnob->AddComponent<ArksEngineComponents::TransformComponent>();
	m_pKnob->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(20,40);
	m_pKnob->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, m_pFileName);
	mGameObj->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
	mGameObj->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);

	mGameObj->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]()->void
		{
			OnKnobClicked();
		});

	m_pSpriteRef = &mGameObj->GetComponent<ArksEngineComponents::SpriteComponent>();
	m_pTransformRef = &mGameObj->GetComponent<ArksEngineComponents::TransformComponent>();
}

void ArksEngineComponents::SliderComponent::Update(double deltaTime)
{
	if (!mDid)
	{
		m_pKnob->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(m_pTransformRef->GetPosition().m_x, m_pTransformRef->GetPosition().m_y - 12);
		m_pKnob->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(0, 255, 0);
		mDid = true;
	}

	if (mGameObj->GetComponent<ArksEngineComponents::ButtonComponent>().IsHovering())
	{
		m_pKnob->GetComponent<SpriteComponent>().SetTextureColor(255,255,0);
	}
	else
	{
		m_pKnob->GetComponent<SpriteComponent>().SetTextureColor(0, 255, 0);
	}

	m_pKnob->Update(deltaTime);
}

void ArksEngineComponents::SliderComponent::Render(float xOffset)
{

	m_pKnob->Render(xOffset);
}

void ArksEngineComponents::SliderComponent::OnKnobClicked()
{
	// Get mouse click location
	auto mouseClickLocation = m_pOwner->GetInput()->GetMouseClickLocation();

	// Move the knob to the clicked position, clamped within the slider bounds
	float newKnobX = std::clamp(static_cast<float>(mouseClickLocation.m_x),
		static_cast<float>(m_pTransformRef->GetPosition().m_x),
		static_cast<float>(m_pTransformRef->GetPosition().m_x + m_pTransformRef->GetScale().m_x));

	// Adjust knob position by its width
	float adjustment = m_pKnob->GetComponent<ArksEngineComponents::TransformComponent>().GetScale().m_x / 2;
	m_pKnob->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(newKnobX - adjustment, m_pTransformRef->GetPosition().m_y - 12);

	// Calculate the value based on the knob's x position on the slider
	float sliderStartX = m_pTransformRef->GetPosition().m_x;
	float sliderEndX = sliderStartX + m_pTransformRef->GetScale().m_x;

	// Map the knob's position to a range of 1-100
	float value = ((newKnobX - sliderStartX) / (sliderEndX - sliderStartX)) * 99.0f + 1.0f;

	// Output or use the value (for debugging, we can print it or store it)
	std::cout << "Slider Value: " << value << std::endl;
}
