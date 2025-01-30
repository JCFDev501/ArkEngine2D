#pragma once
#include <string>

#include "AlignmentComponent.h"
#include "../LocalizationManager.h"
#include "Component.h"

enum TextAlignment
{
	ALIGN_CENTER,        // Aligns the text both horizontally and vertically to the center of the button or UI element.

	ALIGN_TOP_LEFT,      // Aligns the text to the top-left corner of the button or UI element.

	ALIGN_TOP,           // Horizontally centers the text along the top of the button or UI element.

	ALIGN_TOP_RIGHT,     // Aligns the text to the top-right corner of the button or UI element.

	ALIGN_LEFT,          // Vertically centers the text along the left side of the button or UI element.

	ALIGN_RIGHT,         // Vertically centers the text along the right side of the button or UI element.

	ALIGN_BOTTOM_LEFT,   // Aligns the text to the bottom-left corner of the button or UI element.

	ALIGN_BOTTOM,        // Horizontally centers the text along the bottom of the button or UI element.

	ALIGN_BOTTOM_RIGHT   // Aligns the text to the bottom-right corner of the button or UI element.
};

namespace ArksEngine
{
	class Core;
	class Texture;
	class FontManager;
}

namespace ArksEngineComponents
{
	class TransformComponent;

	class TextUiComponent : public Component
	{
		ArksEngine::FontManager* m_pFontManager = nullptr;
		ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;
		std::string m_text;  // Store the text as a std::string to manage memory safely
		Token mToken;
		int m_pFontSize = 0;
		ArksEngine::Core* m_pOwner = nullptr;
		float mPosX = 0;
		float mPosY = 0;
		TextAlignment mAlignment = ALIGN_TOP;  // Default alignment

		float mXOffset = 0;
		float mYOffset = 0;

	public:
		TextUiComponent(ArksEngine::Core* pRenderer, const char* path, int fontSize, const char* pText, Token token = Token::No_Token_Req);

		void Init() override;

		void Update(double deltaTime) override;

		void Render(float xOffset) override;

		void SetAlignment(TextAlignment alignment) { mAlignment = alignment; }  // New setter for alignment

		void SetXOffset(float value) { mXOffset = value * 32; }
		void SetYOffset(float value) { mYOffset = value * 32; }

		void SetText(const char* pText) { m_text = pText; }
		std::string GetText() const { return m_text; }
		
	};
}


