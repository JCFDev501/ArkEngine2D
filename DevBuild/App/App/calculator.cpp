#include "calculator.h"

#include "../ArksEngine/Core.h"
#include "../ArksEngine/GameObject.h"
#include "../ArksEngine/FontManager.h"
#include "../ArksEngine/Components/ButtonComponent.h"
#include "../ArksEngine/Components/ColliderComponent.h"
#include "../ArksEngine/Components/SpriteComponent.h"
#include "../ArksEngine/Components/TextUiComponent.h"
#include "../ArksEngine/Components/TransformComponent.h"
#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>
#include <iomanip>
#include <sstream>

Calculator::Calculator(ArksEngine::Core* pOwner, const char* pFile, int fontSize)
	:m_pOwner(pOwner)
	, mFontSize(fontSize)
	, m_pFile(pFile)
{
}

void Calculator::Update(double deltaTime)
{
	for (auto btn : mButtons)
	{
		btn->Update(deltaTime);
	}
}

void Calculator::Render(float xOffset)
{
	for (auto btn : mButtons)
	{
		btn->Render(xOffset);
	}


    // Get the scale and position of the GameObject from the TransformComponent
    const Vector2F scale = m_pTransformRef->GetScale();
    const Vector2F position = m_pTransformRef->GetPosition();

    // Initial text position (relative to the top-left corner) as floats to retain precision
    float x = position.m_x + 100;
    float y = position.m_y + 120;

    // Render the text, casting only when necessary
    float maxWidth = scale.m_x * mFontSize;
    float maxHeight = scale.m_y * mFontSize;

    // Render each line in the inputLines vector
    for (size_t i = 0; i < mInputLines.size(); ++i)
    {
        // Calculate the rendering position for the current line
        float yOffset = y + i * (mFontSize + 5);  // Add some spacing between lines

        m_pFontManager->RenderTextToScreen(mInputLines[i], ArksEngine::FontManager::BLACK,
            static_cast<int>(x), static_cast<int>(yOffset),
            static_cast<int>(maxWidth), static_cast<int>(maxHeight));
    }
}

void Calculator::Init()
{
    // Ensure TransformComponent exists for the calculator
    m_pTransformRef = &mGameObj->GetComponent<ArksEngineComponents::TransformComponent>();

    // Initialize FontManager and load the font
    m_pFontManager = new ArksEngine::FontManager(m_pOwner);

    // Load a font (assuming font file path and size)
    if (!m_pFontManager->LoadFont(m_pFile, mFontSize))
    {
       //ok
    }

    // Button properties
    const int buttonWidth = 70;
    const int buttonHeight = 50;
    const int buttonSpacing = 15; // Spacing between buttons
    const int buttonsPerRow = 3;  // Number of buttons per row

    ArksEngine::GameObject* newButton = nullptr;

    // Get the starting position of the calculator
    float startX = m_pTransformRef->GetPosition().m_x + 40;
    float startY = m_pTransformRef->GetPosition().m_y + 260;

    // Create buttons 9 to 1
    for (int i = 0; i < 9; ++i)
    {
        newButton = new ArksEngine::GameObject();

        // Add TransformComponent for positioning and scaling
        newButton->AddComponent<ArksEngineComponents::TransformComponent>();

        // Calculate button position (arrange in a grid)
        int row = i / buttonsPerRow; // Calculate the row (0, 1, 2)
        int col = i % buttonsPerRow; // Calculate the column (0, 1, 2)

        // Calculate x and y positions based on row, column, and spacing
        float xPosition = startX + col * (buttonWidth + buttonSpacing);
        float yPosition = startY + row * (buttonHeight + buttonSpacing);

        // Set scale and position
        newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(buttonWidth, buttonHeight);
        newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(xPosition, yPosition);

        // Add SpriteComponent for button visuals
        newButton->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "/CalculatorButton.png");
        newButton->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(225, 225, 225);

        // Add TextUiComponent to display numbers on buttons
        std::string buttonText = std::to_string(9 - i); // Reverse order: 9 to 1
        newButton->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, m_pFile, mFontSize, buttonText.c_str());
        newButton->GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(ALIGN_CENTER);

        newButton->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
        newButton->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);
        newButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, buttonText]() -> void
            {
                std::cout << buttonText;
                ProcessButtonPress(buttonText);
            });

        // Add the button to the list
        mButtons.emplace_back(newButton);
    }

    // Create operator buttons (+, -, *, /, =)
    std::vector<std::string> operators = { "+", "-", "*", "/", "CLR" };
    for (size_t i = 0; i < operators.size(); ++i)
    {
        newButton = new ArksEngine::GameObject();

        // Add TransformComponent for positioning and scaling
        newButton->AddComponent<ArksEngineComponents::TransformComponent>();

        // Position each operator button in the fourth column
        float xPosition = startX + buttonsPerRow * (buttonWidth + buttonSpacing); // Fourth column
        float yPosition = startY + i * (buttonHeight + buttonSpacing);           // Stack vertically

        // Set scale and position
        newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(buttonWidth, buttonHeight);
        newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(xPosition, yPosition);

        // Add SpriteComponent for button visuals
        newButton->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "/CalculatorButton.png");
        newButton->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(255, 255, 255);

        // Add TextUiComponent to display operator symbols
        std::string operatorText = operators[i];
        newButton->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, m_pFile, mFontSize, operatorText.c_str());
        newButton->GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(ALIGN_CENTER);

        newButton->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
        newButton->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);
        newButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, operatorText]() -> void
            {
                std::cout << operatorText;
                ProcessButtonPress(operatorText);
            });

        // Add the button to the list
        mButtons.emplace_back(newButton);
    }

    newButton = nullptr;

    newButton = new ArksEngine::GameObject();

    // Add TransformComponent for positioning and scaling
    newButton->AddComponent<ArksEngineComponents::TransformComponent>();

    // Position each operator button in the fourth column
    float xPosition = startX + 85;
    float yPosition = startY + 195;

    // Set scale and position
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(buttonWidth, buttonHeight);
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(xPosition, yPosition);

    // Add SpriteComponent for button visuals
    newButton->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "/CalculatorButton.png");
    newButton->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(200, 200, 200);

    // Add TextUiComponent to display operator symbols
    std::string operatorText = "0";
    newButton->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, m_pFile, mFontSize, operatorText.c_str());
    newButton->GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(ALIGN_CENTER);

    newButton->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, operatorText]() -> void
        {
            std::cout << operatorText;
            ProcessButtonPress(operatorText);
        });

    // Add the button to the list
    mButtons.emplace_back(newButton);

    newButton = nullptr;

    newButton = new ArksEngine::GameObject();

    // Add TransformComponent for positioning and scaling
    newButton->AddComponent<ArksEngineComponents::TransformComponent>();

    // Position each operator button in the fourth column
    float xPosition2 = startX + 0;
    float yPosition2 = startY + 258;

    // Set scale and position
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(buttonWidth + 175, buttonHeight);
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(xPosition2, yPosition2);

    // Add SpriteComponent for button visuals
    newButton->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "/CalculatorButton.png");
    newButton->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(200, 200, 200);

    // Add TextUiComponent to display operator symbols
    std::string operatorText2 = "=";
    newButton->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, m_pFile, mFontSize, operatorText2.c_str());
    newButton->GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(ALIGN_CENTER);

    newButton->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, operatorText2]() -> void
        {
            std::cout << operatorText2;
            ProcessButtonPress(operatorText2);
        });

    // Add the button to the list
    mButtons.emplace_back(newButton);

    newButton = nullptr;

    newButton = new ArksEngine::GameObject();

    // Add TransformComponent for positioning and scaling
    newButton->AddComponent<ArksEngineComponents::TransformComponent>();

    // Position each operator button in the fourth column
    float xPosition3 = startX + 170;
    float yPosition3 = startY + 195;

    // Set scale and position
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(buttonWidth, buttonHeight);
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(xPosition3, yPosition3);

    // Add SpriteComponent for button visuals
    newButton->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "/CalculatorButton.png");
    newButton->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(200, 200, 200);

    // Add TextUiComponent to display operator symbols
    std::string operatorText3 = ")";
    newButton->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, m_pFile, mFontSize, operatorText3.c_str());
    newButton->GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(ALIGN_CENTER);

    newButton->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, operatorText3]() -> void
        {
            std::cout << operatorText3;
            ProcessButtonPress(operatorText3);
        });

    // Add the button to the list
    mButtons.emplace_back(newButton);

    newButton = nullptr;

    newButton = new ArksEngine::GameObject();

    // Add TransformComponent for positioning and scaling
    newButton->AddComponent<ArksEngineComponents::TransformComponent>();

    // Position each operator button in the fourth column
    float xPosition4 = startX + 0;
    float yPosition4 = startY + 195;

    // Set scale and position
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(buttonWidth, buttonHeight);
    newButton->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(xPosition4, yPosition4);

    // Add SpriteComponent for button visuals
    newButton->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "/CalculatorButton.png");
    newButton->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(200, 200, 200);

    // Add TextUiComponent to display operator symbols
    std::string operatorText4 = "(";
    newButton->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, m_pFile, mFontSize, operatorText4.c_str());
    newButton->GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(ALIGN_CENTER);

    newButton->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);
    newButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, operatorText4]() -> void
        {
            std::cout << operatorText4;
            ProcessButtonPress(operatorText4);
        });

    // Add the button to the list
    mButtons.emplace_back(newButton);

}

void Calculator::ProcessButtonPress(const std::string& buttonText)
{
    // Ensure there is at least one line in the inputLines vector
    if (mInputLines.empty())
    {
        mInputLines.emplace_back("");  // Add an empty string as the first line
    }

    // Get the current line from inputLines (the last one)
    std::string& currentLine = mInputLines.back();

    // Handle special cases
    if (buttonText == "Backspace")
    {
        if (!currentLine.empty())
        {
            // Remove the last character
            currentLine.pop_back();
            mFullInput.pop_back();
        }
        else if (mInputLines.size() > 1)
        {
            // Remove the current line and backtrack to the previous line
            mInputLines.pop_back();
            mInputLines.back().pop_back();
            mFullInput.pop_back();
        }
    }
    else if (buttonText == "CLR")
    {
        // Clear all input
        mFullInput.clear();
        mInputLines.clear();
        mInputLines.emplace_back("");  // Add one empty line
    }
    else if (buttonText == "=")
    {
        // Evaluate the expression without appending "=" to the input
        try
        {
            double result = EvaluateExpression(mFullInput);

            // Format the result properly
            std::ostringstream formattedResult;
            formattedResult << std::fixed << std::setprecision(6) << result;

            // Remove trailing zeros for whole numbers
            std::string resultStr = formattedResult.str();
            if (resultStr.find('.') != std::string::npos)
            {
                resultStr.erase(resultStr.find_last_not_of('0') + 1);
                if (resultStr.back() == '.')
                {
                    resultStr.pop_back();
                }
            }

            // Update display with the result
            mFullInput = resultStr;
            mInputLines.clear();
            mInputLines.emplace_back(mFullInput);
        }
        catch (const std::exception& ex)
        {
            // Print error details to the console
            std::cerr << "Error during evaluation: " << ex.what() << std::endl;
            mFullInput = "Error";  // Update display with "Error"
            mInputLines.clear();
            mInputLines.emplace_back(mFullInput);
        }

    }
    else
    {
        // Append the button text to the input
        currentLine += buttonText;
        mFullInput += buttonText;
    }
}
// Function to evaluate a mathematical expression
double Calculator::EvaluateExpression(const std::string& expression)
{
    // Preprocess the expression to handle implicit multiplication
    std::string processedExpression = PreprocessExpression(expression);

    std::stack<double> numbers;
    std::stack<char> operators;

    auto applyOperator = [](double a, double b, char op) -> double {
        switch (op)
        {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default: throw std::runtime_error("Invalid operator");
        }
        };

    auto precedence = [](char op) -> int {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
        };

    size_t i = 0;
    while (i < processedExpression.size())
    {
        if (isspace(processedExpression[i]))
        {
            ++i;
            continue;
        }

        if (isdigit(processedExpression[i]) || processedExpression[i] == '.')
        {
            size_t j = i;
            while (j < processedExpression.size() && (isdigit(processedExpression[j]) || processedExpression[j] == '.'))
                ++j;

            double number = std::stod(processedExpression.substr(i, j - i));
            numbers.push(number);
            i = j;
        }
        else if (processedExpression[i] == '(')
        {
            operators.push(processedExpression[i]);
            ++i;
        }
        else if (processedExpression[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(applyOperator(a, b, op));
            }

            if (operators.empty() || operators.top() != '(')
                throw std::runtime_error("Mismatched parentheses");

            operators.pop();
            ++i;
        }
        else if (processedExpression[i] == '+' || processedExpression[i] == '-' || processedExpression[i] == '*' || processedExpression[i] == '/')
        {
            // Handle unary operators
            if ((processedExpression[i] == '+' || processedExpression[i] == '-') &&
                (i == 0 || processedExpression[i - 1] == '(' || processedExpression[i - 1] == '+' || processedExpression[i - 1] == '-' ||
                    processedExpression[i - 1] == '*' || processedExpression[i - 1] == '/'))
            {
                // Treat as part of a number
                size_t j = i + 1;
                while (j < processedExpression.size() && (isdigit(processedExpression[j]) || processedExpression[j] == '.'))
                    ++j;

                double number = std::stod(processedExpression.substr(i, j - i));
                numbers.push(number);
                i = j;
                continue;
            }

            while (!operators.empty() &&
                precedence(operators.top()) >= precedence(processedExpression[i]))
            {
                double b = numbers.top(); numbers.pop();
                double a = numbers.top(); numbers.pop();
                char op = operators.top(); operators.pop();
                numbers.push(applyOperator(a, b, op));
            }
            operators.push(processedExpression[i]);
            ++i;
        }
        else
        {
            throw std::runtime_error(std::string("Invalid character in expression: ") + processedExpression[i]);
        }
    }

    while (!operators.empty())
    {
        double b = numbers.top(); numbers.pop();
        double a = numbers.top(); numbers.pop();
        char op = operators.top(); operators.pop();
        numbers.push(applyOperator(a, b, op));
    }

    if (numbers.size() != 1)
        throw std::runtime_error("Invalid expression");

    return numbers.top();
}


std::string Calculator::PreprocessExpression(const std::string& expression)
{
    std::string processed;
    for (size_t i = 0; i < expression.size(); ++i)
    {
        processed += expression[i];

        // Check for implicit multiplication cases:
        // 1. Number followed by '(' (e.g., "5(" -> "5*(")
        if (i > 0 && isdigit(expression[i - 1]) && expression[i] == '(')
        {
            processed.insert(processed.size() - 1, "*");
        }

        // 2. ')' followed by a number or '(' (e.g., ")(2" -> ")*2" or ")((" -> ")*(")
        if (i > 0 && expression[i - 1] == ')' && (isdigit(expression[i]) || expression[i] == '('))
        {
            processed.insert(processed.size() - 1, "*");
        }
    }

    return processed;
}


