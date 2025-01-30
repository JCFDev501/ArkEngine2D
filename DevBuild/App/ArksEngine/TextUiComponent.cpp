#include "TextUiComponent.h"

#include "Core.h"
#include "FontManager.h"
#include "GameObject.h"
#include "Input.h"
#include "Components/TransformComponent.h"
#include "Utillities/Debug_Log.h"

ArksEngineComponents::TextUiComponent::TextUiComponent(ArksEngine::Core* pRenderer, const char* path, int fontSize, const char* pText, Token token)
	:m_pTransformRef(nullptr)
	,m_text(pText)
	,mToken(token)
	,m_pFontSize(fontSize)
	,m_pOwner(pRenderer)
{
	m_pFontManager = new ArksEngine::FontManager(pRenderer);

	m_pFontManager->LoadFont(path, fontSize);
}

void ArksEngineComponents::TextUiComponent::Init()
{
	// Let's Get a ref to our transform
	m_pTransformRef = &mGameObj->GetComponent<TransformComponent>();
}

void ArksEngineComponents::TextUiComponent::Update(double deltaTime)
{
	
}

void ArksEngineComponents::TextUiComponent::Render(float xOffset)
{
    // Get the scale of the GameObject from the TransformComponent
    auto scale = m_pTransformRef->GetScale();

    // Calculate the bounds based on the GameObject's position and scale
    float maxWidth = m_pTransformRef->GetScale().m_x * m_pFontSize;  
    float maxHeight = m_pTransformRef->GetScale().m_y * m_pFontSize;

    if (mToken == Token::No_Token_Req)
    {
        // Use the current text stored in m_text
        m_pFontManager->RenderTextToScreen(m_text, ArksEngine::FontManager::BLACK,
            static_cast<int>(m_pTransformRef->GetPosition().m_x + mPosX * 32),
            static_cast<int>(m_pTransformRef->GetPosition().m_y + mPosY * 32),
            static_cast<int>(maxWidth), static_cast<int>(maxHeight));
    }
    else
    {
        // Get the localized text
        m_text = m_pOwner->GetLocalizationManager()->GetTranslation(mToken);

        // Render the localized text
        m_pFontManager->RenderTextToScreen(m_text, ArksEngine::FontManager::BLACK,
            static_cast<int>(m_pTransformRef->GetPosition().m_x + mPosX * 32),
            static_cast<int>(m_pTransformRef->GetPosition().m_y + mPosY * 32),
            static_cast<int>(maxWidth), static_cast<int>(maxHeight));
    }

	
}
