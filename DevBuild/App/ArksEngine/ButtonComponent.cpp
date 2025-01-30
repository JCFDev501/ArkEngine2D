#include "ButtonComponent.h"

#include "Core.h"
#include "GameObject.h"
#include "Input.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Utillities/Debug_Log.h"

ArksEngineComponents::ButtonComponent::ButtonComponent(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}

void ArksEngineComponents::ButtonComponent::SetButtonHoverColor(uint8_t r, uint8_t g, uint8_t b)
{
    m_buttonHoverColor = { r, g, b };
}

bool ArksEngineComponents::ButtonComponent::HitTest(int x, int y) const
{
	return (x >= m_pTransformRef->GetPosition().m_x && x < +m_pTransformRef->GetPosition().m_x + m_pTransformRef->GetScale().m_x &&
		y >= m_pTransformRef->GetPosition().m_y && y < +m_pTransformRef->GetPosition().m_y + m_pTransformRef->GetScale().m_y);
}

void ArksEngineComponents::ButtonComponent::Init()
{
	// Let's Get a ref to our transform
	m_pTransformRef = &mGameObj->GetComponent<TransformComponent>();

    // Ref to our sprite
    m_pSpriteRef = &mGameObj->GetComponent<SpriteComponent>();
}

void ArksEngineComponents::ButtonComponent::Update(double deltaTime)
{

    if (!m_hasButtonOriginalColor)
    {
        m_buttonHoverColor.m_originalColor = m_pSpriteRef->GetTextureColor();
        m_hasButtonOriginalColor = true;
    }
    


    // Check if the left mouse button is pressed
    bool isLeftClickPressed = m_pOwner->GetInput()->GetKeyPressed(ArksEngine::Input::Left_Click);

    if (isLeftClickPressed && !m_wasLeftClickPressed)  
    {
        auto mouseClickLocation = m_pOwner->GetInput()->GetMouseClickLocation();
        if (mouseClickLocation.m_x != 0 && mouseClickLocation.m_y != 0)
        {
            if (HitTest(mouseClickLocation.m_x, mouseClickLocation.m_y))
            {
                Trigger();
            }
        }
    }

    // Update the previous click state to the current state
    m_wasLeftClickPressed = isLeftClickPressed;

    auto mouseHoverLocation = m_pOwner->GetInput()->GetMouseHoverLocation();
    bool isHovered = HitTest(mouseHoverLocation.m_x, mouseHoverLocation.m_y);

    // Only change the texture color if the hover state changes
    if (isHovered != m_wasHovered)  // Hover state has changed
    {
        if (isHovered)
        {
            // Set the texture color to hover color when hovered
            m_pSpriteRef->SetTextureColor(m_buttonHoverColor.m_r, m_buttonHoverColor.m_g, m_buttonHoverColor.m_b);
        }
        else
        {
            // Reset the texture color to the original when not hovered
            m_pSpriteRef->SetTextureColor(m_buttonHoverColor.m_originalColor.m_r, m_buttonHoverColor.m_originalColor.m_g, m_buttonHoverColor.m_originalColor.m_b);
        }

        // Update the hover state
        m_wasHovered = isHovered;
    }
}

void ArksEngineComponents::ButtonComponent::Trigger() const
{
	if (m_callback != nullptr)
	{
		m_callback();
	}
}

