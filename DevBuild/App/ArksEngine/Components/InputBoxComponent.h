#pragma once
#include <string>
#include <unordered_map>

#include "Component.h"

namespace ArksEngine
{
	class FontManager;
	class Core;
}

namespace ArksEngineComponents
{
	class TransformComponent;

	class InputBoxComponent : public Component
	{
		// A map to track whether each key is pressed or not
		std::unordered_map<int, bool> mKeyState;
		// A pointer to the Core class
		ArksEngine::Core* m_pOwner = nullptr;
		// A boolean to track whether the Caps Lock key is pressed
		bool m_CapsLock = false;
		// A boolean to track whether the Shift key is pressed
		bool mKeyPressed;

		// A pointer to the FontManager class
		ArksEngine::FontManager* m_pFontManager = nullptr;
		// For text input and rendering
		std::string inputText;  // To store the input text
		// The font size
		int mFontSize = 0;
		// The file path for the font
		const char* m_pFile = nullptr;

		// A pointer to the TransformComponent class
		ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;

		bool showCursor = true;  // Control whether the cursor is visible
		double cursorBlinkTimer = 0.0;  // Timer for blinking effect
		const double blinkInterval = 0.5;  // Blink interval in seconds

		float mXOffset = 3;
		float mYOffset = 0;

		std::vector<std::string> mInputLines;

		float mWrapOffsetX = 0;
		float mWrapOffsetY = 0;

		std::string mFullInput = "";  // To store the full input without word wrapping
		

	public:
		InputBoxComponent(ArksEngine::Core* pOwner, const char* pFile, int fontSize, float wrapOffsetX = 0, float wrapOffsetY = 0);

		void Init() override;

		void Update(double deltaTime) override;
		void Render(float xOffset) override;

		void ExitMenu();

	private:

		void ProcessInput();
		void CheckWordWrapping(std::string& currentLine);
	};
}

