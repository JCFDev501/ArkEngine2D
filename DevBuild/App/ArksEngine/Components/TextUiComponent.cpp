#include "TextUiComponent.h"

#include "../Core.h"
#include "../FontManager.h"
#include "../GameObject.h"
#include "../Input.h"
#include "TransformComponent.h"
#include "../Utillities/Debug_Log.h"

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
    // Get the scale and position of the GameObject from the TransformComponent
    const Vector2F scale = m_pTransformRef->GetScale();
    const Vector2F position = m_pTransformRef->GetPosition();

    // Calculate the bounds based on the GameObject's position and scale
    const float objectWidth = scale.m_x;
    const float objectHeight = scale.m_y;

    // Get the text (localized if necessary) and calculate its dimensions
    std::string renderText = m_text;
    if (mToken != Token::No_Token_Req)
    {
        renderText = m_pOwner->GetLocalizationManager()->GetTranslation(mToken);
    }

    // Calculate text dimensions
    const float textWidth = static_cast<float>(m_pFontManager->GetTextWidth(renderText, m_pFontSize));
    const float textHeight = static_cast<float>(m_pFontManager->GetTextHeight(renderText, m_pFontSize));

    // Initial text position (relative to the top-left corner) as floats to retain precision
    float x = position.m_x;
    float y = position.m_y;

    // Alignment logic, keeping calculations in float
    switch (mAlignment)
    {
    case ALIGN_CENTER:
        x += (objectWidth / 2.0f) - (textWidth / 2.0f);
        y += (objectHeight / 2.0f) - (textHeight / 2.0f);
        break;

    case ALIGN_TOP_LEFT:
        // Already aligned to top-left by default
        break;

    case ALIGN_TOP:
        x += (objectWidth / 2.0f) - (textWidth / 2.0f);
        break;

    case ALIGN_TOP_RIGHT:
        x += objectWidth - textWidth;
        break;

    case ALIGN_LEFT:
        y += (objectHeight / 2.0f) - (textHeight / 2.0f);
        break;

    case ALIGN_RIGHT:
        x += objectWidth - textWidth;
        y += (objectHeight / 2.0f) - (textHeight / 2.0f);
        break;

    case ALIGN_BOTTOM_LEFT:
        y += objectHeight - textHeight;
        break;

    case ALIGN_BOTTOM:
        x += (objectWidth / 2.0f) - (textWidth / 2.0f);
        y += objectHeight - textHeight;
        break;

    case ALIGN_BOTTOM_RIGHT:
        x += objectWidth - textWidth;
        y += objectHeight - textHeight;
        break;
    }

    // Apply offsets, retaining precision
    x += mXOffset - xOffset;
    y += mYOffset;

    // Render the text, casting only when necessary
    float maxWidth = scale.m_x * m_pFontSize;
    float maxHeight = scale.m_y * m_pFontSize;

    m_pFontManager->RenderTextToScreen(renderText, ArksEngine::FontManager::BLACK,
        static_cast<int>(x), static_cast<int>(y),
        maxWidth, maxHeight);
}


