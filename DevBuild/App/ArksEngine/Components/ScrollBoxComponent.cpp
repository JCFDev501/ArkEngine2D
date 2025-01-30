#include "ScrollBoxComponent.h"

#include "ButtonComponent.h"
#include "SpriteComponent.h"
#include "TextUiComponent.h"
#include "TransformComponent.h"
#include "../Core.h"

#include "../GameObject.h"
#include "../Input.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()

ArksEngineComponents::ScrollBoxComponent::ScrollBoxComponent(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}

void ArksEngineComponents::ScrollBoxComponent::AddGameObject(ArksEngine::GameObject* pGameObject)
{
	m_gameObjects.push_back(pGameObject);
}

void ArksEngineComponents::ScrollBoxComponent::Init()
{
	m_pTransformRef = &mGameObj->GetComponent<ArksEngineComponents::TransformComponent>();
	width = m_pTransformRef->GetScale().m_x;
	height = m_pTransformRef->GetScale().m_y;
    totalButtonHeight = 24 * BUTTON_HEIGHT;
}

void ArksEngineComponents::ScrollBoxComponent::Update(double deltaTime)
{
    width = m_pTransformRef->GetScale().m_x;
    height = m_pTransformRef->GetScale().m_y;

	for (auto gameObject: m_gameObjects)
	{
		gameObject->Update(deltaTime);
	}

	ProccessInput();
}

void ArksEngineComponents::ScrollBoxComponent::Render(float xOffset)
{
	for (auto gameObject : m_gameObjects)
	{
		gameObject->Render(xOffset);
	}
}

// THIS METHOD IS SPECIFIC FOR THE HW REMEMBER TO GET RID OF IT DURING THE BREAK?!?!?!?!?!?!?!?!?!?!
void ArksEngineComponents::ScrollBoxComponent::CreateNumAmoutOfButtons(int amount)
{

    // Initialize random song names
    std::vector<std::string> songNames =
    {
        "Bohemian Rhapsody",
        "Hotel California",
        "Stairway to Heaven",
        "Imagine",
        "Hey Jude",
        "Smells Like Teen Spirit",
        "Sweet Child O' Mine",
        "Billie Jean",
        "Shape of You",
        "Blinding Lights",
        "Hallelujah",
        "Rolling in the Deep",
        "Wonderwall",
        "Let it Be",
        "Someone Like You",
        "Uptown Funk",
        "Shake it Off",
        "Lose Yourself",
        "I Will Survive",
        "We Are the Champions",
        "Thinking Out Loud",
        "Despacito",
        "Old Town Road",
        "Bad Guy"
    };


    // Seed the random number generator
    std::srand(std::time(nullptr));

    float buttonOffset = 0;
    int songCount = songNames.size(); // Total number of songs in the list

    for (int i = 0; i < amount; i++)
    {
        // Create a new button GameObject
        ArksEngine::GameObject* button = new ArksEngine::GameObject();
        button->AddComponent<ArksEngineComponents::TransformComponent>();

        // Set position and scale
        button->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(
			m_pTransformRef->GetPosition().m_x + 19.5 * 32, // TODO: Fix this magic number
            m_pTransformRef->GetPosition().m_y + buttonOffset
        );
        button->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(width, 100);

        // Add a sprite component for visual representation
        button->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "../../App/Assets/StartButton.png");
        button->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(0, 255, 0);

        // Add a button component and set hover color
        button->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
        button->GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(255, 255, 0);

        // Sequentially select a song name
        std::string songName = songNames[i % songCount]; // Loop back if the number of buttons exceeds the song list size

        // Add a TextUiComponent with the song name
        button->AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, "Assets/comicbd.ttf", 20, songName.c_str());
        button->GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(ALIGN_CENTER);
        button->GetComponent<ArksEngineComponents::TextUiComponent>().SetXOffset(0);
        button->GetComponent<ArksEngineComponents::TextUiComponent>().SetYOffset(0);

        // Add click logic to display song name
        button->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, songName]() -> void
            {
                system("cls");
                std::cout << "Song: " << songName << std::endl;
            });

        // Update the button offset for the next button
        buttonOffset += button->GetComponent<ArksEngineComponents::TransformComponent>().GetScale().m_y;

        // Add the button to the scroll box
        AddGameObject(button);
    }

}

void ArksEngineComponents::ScrollBoxComponent::ProccessInput()
{
    const float SCROLL_SPEED = 0.1f;     // Smooth scroll speed for arrow keys
    const float PAGE_SCROLL_AMOUNT = 700; // Page scroll is equal to the height of the scroll box

    // Track key press states for Page Up and Page Down
    static bool pageUpPressed = false;
    static bool pageDownPressed = false;

    // Smooth scroll up (Arrow Up)
    if (m_pOwner->GetInput()->GetKeyPressed(ArksEngine::Input::KeyCode_UpArrow))
    {
        for (auto gameObject : m_gameObjects)
        {
            auto& transform = gameObject->GetComponent<ArksEngineComponents::TransformComponent>();
            transform.SetPosition(
                transform.GetPosition().m_x,
                transform.GetPosition().m_y - SCROLL_SPEED
            );
        }
    }

    // Snap scroll up (Page Up)
    if (m_pOwner->GetInput()->GetKeyPressed(ArksEngine::Input::KeyCode_PageUp))
    {
        if (!pageUpPressed) // Only execute once per keypress
        {
            for (auto gameObject : m_gameObjects)
            {
                auto& transform = gameObject->GetComponent<ArksEngineComponents::TransformComponent>();
                transform.SetPosition(
                    transform.GetPosition().m_x,
                    transform.GetPosition().m_y - PAGE_SCROLL_AMOUNT
                );
            }
            pageUpPressed = true;
        }
    }
    else
    {
        pageUpPressed = false; // Reset state when key is released
    }

    // Smooth scroll down (Arrow Down)
    if (m_pOwner->GetInput()->GetKeyPressed(ArksEngine::Input::KeyCode_DownArrow))
    {
        for (auto gameObject : m_gameObjects)
        {
            auto& transform = gameObject->GetComponent<ArksEngineComponents::TransformComponent>();
            transform.SetPosition(
                transform.GetPosition().m_x,
                transform.GetPosition().m_y + SCROLL_SPEED
            );
        }
    }

    // Snap scroll down (Page Down)
    if (m_pOwner->GetInput()->GetKeyPressed(ArksEngine::Input::KeyCode_PageDown))
    {
        if (!pageDownPressed) // Only execute once per keypress
        {
            for (auto gameObject : m_gameObjects)
            {
                auto& transform = gameObject->GetComponent<ArksEngineComponents::TransformComponent>();
                transform.SetPosition(
                    transform.GetPosition().m_x,
                    transform.GetPosition().m_y + PAGE_SCROLL_AMOUNT
                );
            }
            pageDownPressed = true;
        }
    }
    else
    {
        pageDownPressed = false; // Reset state when key is released
    }

    // Dynamic wrapping logic
    for (auto gameObject : m_gameObjects)
    {
        auto& transform = gameObject->GetComponent<ArksEngineComponents::TransformComponent>();
        float yPos = transform.GetPosition().m_y;

        // Wrap from top to bottom
        if (yPos < -BUTTON_HEIGHT)
        {
            transform.SetPosition(
                transform.GetPosition().m_x,
                yPos + totalButtonHeight
            );
        }

        // Wrap from bottom to top
        if (yPos > totalButtonHeight - BUTTON_HEIGHT)
        {
            transform.SetPosition(
                transform.GetPosition().m_x,
                yPos - totalButtonHeight
            );
        }
    }
}




