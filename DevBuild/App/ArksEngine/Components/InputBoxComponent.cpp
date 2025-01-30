#include "InputBoxComponent.h"

#include <map>
#include "TransformComponent.h"
#include "TextUiComponent.h"
#include "../FontManager.h"
#include "../Core.h"
#include "../Input.h"
#include "../Utillities/Debug_Log.h"
#include "../GameObject.h"

ArksEngineComponents::InputBoxComponent::InputBoxComponent(ArksEngine::Core* pOwner, const char* pFile, int fontSize, float wrapOffsetX, float wrapOffsetY)
	:m_pOwner(pOwner)
	,mFontSize(fontSize)
	,m_pFile(pFile)
	,mWrapOffsetX(wrapOffsetX * 32)
	,mWrapOffsetY(wrapOffsetY * 32)
{
}

void ArksEngineComponents::InputBoxComponent::Init()
{
	// Initialize FontManager and load the font
	m_pFontManager = new ArksEngine::FontManager(m_pOwner);

	// Load a font (assuming font file path and size)
	if (!m_pFontManager->LoadFont(m_pFile, mFontSize)) 
	{
		m_pOwner->GetDebug_Log()->Log("Failed to load font");
	}

	// Get a reference to the TransformComponent
	m_pTransformRef = &mGameObj->GetComponent<TransformComponent>();
	if (m_pTransformRef == nullptr)
	{
		m_pOwner->GetDebug_Log()->Log("Failed to get TransformComponent");
	}
}

void ArksEngineComponents::InputBoxComponent::Update(double deltaTime)
{
    // Update the cursor blink timer
    cursorBlinkTimer += deltaTime;
    if (cursorBlinkTimer >= blinkInterval)
    {
        showCursor = !showCursor;  // Toggle cursor visibility
        cursorBlinkTimer = 0.0;
    }


	// Check for key presses only if a key has not already been pressed
	if (!mKeyPressed)
	{
		ProcessInput();  // Process the input only if a key has not been pressed
	}
}

void ArksEngineComponents::InputBoxComponent::Render(float xOffset)
{
    // Get the scale and position of the GameObject from the TransformComponent
    const Vector2F scale = m_pTransformRef->GetScale();
    const Vector2F position = m_pTransformRef->GetPosition();

    // Initial text position (relative to the top-left corner) as floats to retain precision
    float x = position.m_x + 32;
    float y = position.m_y + 32;

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

    // Render the cursor if it should be visible
    if (showCursor)
    {
        // Get the position for the cursor (at the end of the last line)
        float cursorX = x + m_pFontManager->GetTextWidth(mInputLines.back(), mFontSize);
        float cursorY = y + (mInputLines.size() - 1) * (mFontSize + 5);  // On the last line

        // Render the cursor as a vertical bar (adjust height as needed)
        m_pFontManager->RenderTextToScreen("|", ArksEngine::FontManager::BLACK,
            static_cast<int>(cursorX), static_cast<int>(cursorY),
            static_cast<int>(maxWidth), static_cast<int>(maxHeight));
    }
}

void ArksEngineComponents::InputBoxComponent::ExitMenu()
{
    // Ensure mFullInput is valid before printing
    if (!mFullInput.empty())
    {
        std::cout << "Full input: " << mFullInput << std::endl;
    }
    else
    {
        std::cout << "Full input is empty." << std::endl;
    }
}

void ArksEngineComponents::InputBoxComponent::ProcessInput()
{
    ArksEngine::Input* pInput = m_pOwner->GetInput();
    bool isCapsLock = pInput->GetKeyPressed(ArksEngine::Input::KeyCode_CapsLock);
    bool isShiftPressed = pInput->GetKeyPressed(ArksEngine::Input::KeyCode_Shift);

    // Ensure there is at least one line in the inputLines vector
    if (mInputLines.empty())
    {
        mInputLines.emplace_back("");  // Add an empty string as the first line

        if (!mFullInput.empty())
		{
            mFullInput.pop_back();   // Also remove it from the full input string
		}
        
    }

    // Get the current line from inputLines (the last one)
    std::string& currentLine = mInputLines.back();

    // Handle Backspace input
    bool isBackspacePressed = pInput->GetKeyPressed(ArksEngine::Input::KeyCode_Backspace);
    if (isBackspacePressed && !mKeyState[ArksEngine::Input::KeyCode_Backspace])
    {
        if (!currentLine.empty())
        {
            // If there is text on the current line, remove the last character
            currentLine.pop_back();
            mFullInput.pop_back();  // Remove from the full input string as well
        }
        else if (mInputLines.size() > 1)
        {
            // If the current line is empty and there are previous lines
            mInputLines.pop_back();  // Remove the current empty line
            mInputLines.back().pop_back();  // Remove the last character of the previous line
            mFullInput.pop_back();   // Remove from full input
        }

        mKeyState[ArksEngine::Input::KeyCode_Backspace] = true;  // Mark key as pressed
    }
    else if (!isBackspacePressed && mKeyState[ArksEngine::Input::KeyCode_Backspace])
    {
        mKeyState[ArksEngine::Input::KeyCode_Backspace] = false;  // Reset key state when released
    }

    // Iterate through all letter keys (A-Z)
    for (int key = ArksEngine::Input::KeyCode_A; key <= ArksEngine::Input::KeyCode_Z; ++key)
    {
        ArksEngine::Input::KeyCode keyCode = static_cast<ArksEngine::Input::KeyCode>(key);
        bool keyCurrentlyPressed = pInput->GetKeyPressed(keyCode);

        if (keyCurrentlyPressed && !mKeyState[key])
        {
            char letter = 'a' + (key - ArksEngine::Input::KeyCode_A);  // Default to lowercase
            if (isCapsLock || isShiftPressed)
            {
                letter = static_cast<char>(toupper(letter));
            }

            // Add the letter to the current line
            currentLine += letter;
            mFullInput += letter;  // Also add it to the full input string
           

            // Check if the current line needs to be wrapped
            CheckWordWrapping(currentLine);

            mKeyState[key] = true;  // Mark key as pressed
        }
        else if (!keyCurrentlyPressed && mKeyState[key])
        {
            mKeyState[key] = false;  // Reset key state when released
        }
    }

    // Handle numbers (1-9) first
    for (int key = ArksEngine::Input::KeyCode_One; key <= ArksEngine::Input::KeyCode_Nine; ++key)
    {
        ArksEngine::Input::KeyCode keyCode = static_cast<ArksEngine::Input::KeyCode>(key);
        bool keyCurrentlyPressed = pInput->GetKeyPressed(keyCode);

        if (keyCurrentlyPressed && !mKeyState[key])
        {
            char character = '1' + (key - ArksEngine::Input::KeyCode_One);  // Default to number (1-9)

            // If Shift is pressed, handle Shift-modified characters
            if (isShiftPressed)
            {
                switch (key)
                {
                case ArksEngine::Input::KeyCode_One:    
                    character = '!';
                	break;
                case ArksEngine::Input::KeyCode_Two:   
                    character = '@';
                	break;
                case ArksEngine::Input::KeyCode_Three: 
                    character = '#';
                	break;
                case ArksEngine::Input::KeyCode_Four:  
                    character = '$';
                	break;
                case ArksEngine::Input::KeyCode_Five:  
                    character = '%';
                	break;
                case ArksEngine::Input::KeyCode_Six:   
                    character = '^';
                	break;
                case ArksEngine::Input::KeyCode_Seven: 
                    character = '&';
                	break;
                case ArksEngine::Input::KeyCode_Eight: 
                    character = '*';
                	break;
                case ArksEngine::Input::KeyCode_Nine:  
                    character = '(';
                	break;
                }
            }

            currentLine += character;
            mFullInput += character;  // Add to the full input string

            // Check word wrapping for the numeric and special character
            CheckWordWrapping(currentLine);

            mKeyState[key] = true;  // Mark key as pressed
        }
        else if (!keyCurrentlyPressed && mKeyState[key])
        {
            mKeyState[key] = false;  // Reset key state when released
        }
    }

    // Handle zero key separately (since it's not in the 1-9 range)
    bool keyZeroPressed = pInput->GetKeyPressed(ArksEngine::Input::KeyCode_Zero);
    if (keyZeroPressed && !mKeyState[ArksEngine::Input::KeyCode_Zero])
    {
        char character = '0';  // Default to zero

        if (isShiftPressed)
        {
            character = ')';  // Shift + 0 = )
        }

        currentLine += character;
        mFullInput += character;  // Add to the full input string

        // Check word wrapping for the zero key
        CheckWordWrapping(currentLine);

        mKeyState[ArksEngine::Input::KeyCode_Zero] = true;  // Mark key as pressed
    }
    else if (!keyZeroPressed && mKeyState[ArksEngine::Input::KeyCode_Zero])
    {
        mKeyState[ArksEngine::Input::KeyCode_Zero] = false;  // Reset key state when released
    }

    // Process special characters like /, ., , (with or without Shift)
    std::map<ArksEngine::Input::KeyCode, std::pair<char, char>> specialKeys =
    {
        {ArksEngine::Input::KeyCode_Slash, {'/', '?'}},
        {ArksEngine::Input::KeyCode_Period, {'.', '>'}},
        {ArksEngine::Input::KeyCode_Comma, {',', '<'}},
        {ArksEngine::Input::KeyCode_Minus, {'-', '_'}},
        {ArksEngine::Input::KeyCode_Equals, {'=', '+'}}
    };

    for (const auto& [keyCode, characters] : specialKeys)
    {
        bool keyCurrentlyPressed = pInput->GetKeyPressed(keyCode);

        if (keyCurrentlyPressed && !mKeyState[keyCode])
        {
            char character = isShiftPressed ? characters.second : characters.first;
            currentLine += character;
            mFullInput += character;  // Add to the full input string

            // Check word wrapping for the special characters
            CheckWordWrapping(currentLine);

            mKeyState[keyCode] = true;  // Mark key as pressed
        }
        else if (!keyCurrentlyPressed && mKeyState[keyCode])
        {
            mKeyState[keyCode] = false;  // Reset key state when released
        }
    }

    // Handle space input
    if (pInput->GetKeyPressed(ArksEngine::Input::KeyCode_Space) && !mKeyState[ArksEngine::Input::KeyCode_Space])
    {
        currentLine += ' ';  // Add space to the current line
        mFullInput += ' ';   // Also add space to the full input string

        // Check word wrapping for spaces
        CheckWordWrapping(currentLine);

        mKeyState[ArksEngine::Input::KeyCode_Space] = true;
    }
    else if (!pInput->GetKeyPressed(ArksEngine::Input::KeyCode_Space) && mKeyState[ArksEngine::Input::KeyCode_Space])
    {
        mKeyState[ArksEngine::Input::KeyCode_Space] = false;
    }
}

// Helper function to handle word wrapping
void ArksEngineComponents::InputBoxComponent::CheckWordWrapping(std::string& currentLine)
{
    // Calculate the total width of the current line
    int currentLineWidth = m_pFontManager->GetTextWidth(currentLine, mFontSize);

    // Get the width of the game object
    float gameObjWidth = m_pTransformRef->GetScale().m_x + mWrapOffsetX;

    // Check if the current line exceeds the game object's width
    if (currentLineWidth > static_cast<int>(gameObjWidth))
    {
        // Split the current line at the last space
        size_t lastSpace = currentLine.find_last_of(' ');
        if (lastSpace != std::string::npos)
        {
            // Move the word after the last space to a new line
            std::string newLine = currentLine.substr(lastSpace + 1);  // Get the word after the space
            currentLine.erase(lastSpace);  // Remove the word from the current line

            // Calculate the total height of all lines, including the new one
            float totalTextHeight = (mFontSize + 5) * (mInputLines.size() + 1) + mWrapOffsetY;  // Add one for the new line

            // Before adding a new line, check if it fits within the box's height
            if (totalTextHeight <= m_pTransformRef->GetScale().m_y)
            {
                mInputLines.push_back(newLine);  // Add the new line to the vector if within the height limit
            }
        }
        else
        {
            // If no space is found, wrap the entire line to a new line
            if (mInputLines.size() * (mFontSize + 5) < m_pTransformRef->GetScale().m_y)
            {
                mInputLines.push_back(currentLine);
                currentLine.clear();
            }
        }
    }
}





