#pragma once
#include <string>
#include <vector>

#include "../ArksEngine/Components/Component.h"

namespace ArksEngineComponents
{
	class TransformComponent;
}

namespace ArksEngine
{
	class FontManager;
	class Core;
}

class Calculator : public ArksEngineComponents::Component
{
	// A pointer to the Core class
	ArksEngine::Core* m_pOwner = nullptr;

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

	// List of all buttons
	std::vector<ArksEngine::GameObject*> mButtons;

	std::vector<std::string> mInputLines;



	std::string mFullInput = "";  // To store the full input without word wrapping
public:
	Calculator(ArksEngine::Core* pOwner, const char* pFile, int fontSize);

	void Update(double deltaTime) override;

	void Render(float xOffset) override;

	void Init() override;

	void ProcessButtonPress(const std::string& buttonText);

	double EvaluateExpression(const std::string& expression);

	std::string PreprocessExpression(const std::string& expression);
};

