#include "AlignmentComponent.h"

#include "TransformComponent.h"
#include "../Core.h"
#include "../GameObject.h"
#include "../Window.h"

ArksEngineComponents::AlignmentComponent::AlignmentComponent(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}

void ArksEngineComponents::AlignmentComponent::Init()
{
	m_ScreenWidth = m_pOwner->GetWindow()->GetScreenWidth();
	m_ScreenHeight = m_pOwner->GetWindow()->GetScreenHeight();

	m_pTransformRef = &mGameObj->GetComponent<TransformComponent>();
}

void ArksEngineComponents::AlignmentComponent::Update(double deltaTime)
{
    // Get the object's scale
    Vector2F scale = m_pTransformRef->GetScale();

    float objectWidth = scale.m_x;  // Scaled width
    float objectHeight = scale.m_y; // Scaled height

    // Initial position
    float x = 0.0f;
    float y = 0.0f;

    // Common centering logic
    float centerX = (m_ScreenWidth / 2.0f) - (objectWidth / 2.0f);
    float centerY = (m_ScreenHeight / 2.0f) - (objectHeight / 2.0f);

    // Switch case for alignment
    switch (m_pAligment)
    {
    case CENTER:
        x = centerX;
        y = centerY;
        break;

    case TOP:
        x = centerX;
        y = 0;
        break;

    case BOTTOM:
        x = centerX;
        y = m_ScreenHeight - objectHeight;
        break;

    case LEFT:
        x = 0;
        y = centerY;
        break;

    case RIGHT:
        x = m_ScreenWidth - objectWidth;
        y = centerY;
        break;

    case TOP_LEFT:
        x = 0;
        y = 0;
        break;

    case TOP_RIGHT:
        x = m_ScreenWidth - objectWidth;
        y = 0;
        break;

    case BOTTOM_LEFT:
        x = 0;
        y = m_ScreenHeight - objectHeight;
        break;

    case BOTTOM_RIGHT:
        x = m_ScreenWidth - objectWidth;
        y = m_ScreenHeight - objectHeight;
        break;

    case CENTER_LEFT:
        x = 0;
        y = centerY;
        break;

    case CENTER_RIGHT:
        x = m_ScreenWidth - objectWidth;
        y = centerY;
        break;

    case CENTER_TOP:
        x = centerX;
        y = 0;
        break;

    case CENTER_BOTTOM:
        x = centerX;
        y = m_ScreenHeight - objectHeight;
        break;
    }

    // Apply offsets
    x += m_OffsetX;
    y += m_OffsetY;

    // Set the new position with floating-point precision
    m_pTransformRef->SetPosition(static_cast<int>(x), static_cast<int>(y));
}


void ArksEngineComponents::AlignmentComponent::SetAlignment(Alignment alignment)
{
	m_pAligment = alignment;
}

void ArksEngineComponents::AlignmentComponent::SetOffset(int offsetX, int offsetY)
{
    float unit = m_ScreenWidth / m_ScreenHeight * 32;

    m_OffsetX = offsetX * unit;
    m_OffsetY = offsetY * unit;
}
