#include "GameObjectBuilder.h"
#include "../Utillities/tinyxml2.h"
#include <cstdlib>
#include <iostream>
#include <ostream>

#include "../Components/ButtonComponent.h"
#include "../Core.h"
#include "../Components/ControllerComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/SpriteComponent.h"
#include "../GameObject.h"
#include "../GameObjectManager.h"
#include "../LuaSystem.h"
#include "../Components/AlignmentComponent.h"
#include "../Components/CheckBoxComponent.h"
#include "../Components/TextUiComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/InputBoxComponent.h"
#include "../Components/SliderComponent.h"
#include "../Components/ToggleBoxComponent.h"

ArksEngineBuilders::GameObjectBuilder::GameObjectBuilder(ArksEngine::Core* pOwner, ArksEngine::GameObjectManager* pManager)
	:m_pOwner(pOwner)
	,m_pEntityManager(pManager)
{
}

ArksEngine::GameObject* ArksEngineBuilders::GameObjectBuilder::CreateGameObject(const char* pXml_File) const
{
	// Create a new entity and add it to the entity manager
	ArksEngine::GameObject& game_object(m_pEntityManager->AddGameObject());

	// Load the XML file
	tinyxml2::XMLDocument doc;
	doc.LoadFile(pXml_File);

	// Get the active attribute from the gameObject element
	const tinyxml2::XMLElement* gameObjectElement = doc.FirstChildElement("gameObject");
	if (gameObjectElement)
	{
		const char* activeAttribute = gameObjectElement->Attribute("active");
		if (activeAttribute)
		{
			bool isActive = strcmp(activeAttribute, "true") == 0;
			game_object.SetActive(isActive);
		}
	}

	// Get the name of the entity from the XML file and set it
	const tinyxml2::XMLElement* elementTag = doc.FirstChildElement()->FirstChildElement();
	const char* pName = elementTag->GetText();
	game_object.SetName(pName);

	// Get the tag of the entity from the XML file and set it
	elementTag = doc.FirstChildElement("gameObject")->FirstChildElement()->NextSiblingElement();
	const char* pTag = elementTag->GetText();
	game_object.SetTag(pTag);

	// Move to the next element (the first component)
	elementTag = elementTag->NextSiblingElement();

	const tinyxml2::XMLElement* elementChild = elementTag;

	// Iterate through all component elements in the XML file
	while (elementTag)
	{
		// Get the component type
		const char* pComponentType = elementTag->Attribute("name");
		std::string componentType = pComponentType;

		// Handle each component type
		if (componentType == "TransformComponent")
		{
			// Get position, rotation, and scale values from the XML file
			// and add a TransformComponent to the entity with those values
			elementChild = elementTag->FirstChildElement();
			const char* pPositionX = elementChild->GetText();
			float positionX = std::atof(pPositionX);

			elementChild = elementChild->NextSiblingElement();
			const char* pPositionY = elementChild->GetText();
			float positionY = std::atof(pPositionY);

			elementChild = elementChild->NextSiblingElement();
			const char* pRotationX = elementChild->GetText();
			float rotationX = std::atof(pRotationX);

			elementChild = elementChild->NextSiblingElement();
			const char* pRotationY = elementChild->GetText();
			float rotationY = std::atof(pRotationY);

			elementChild = elementChild->NextSiblingElement();
			const char* pScaleX = elementChild->GetText();
			float scaleX = std::atof(pScaleX);

			elementChild = elementChild->NextSiblingElement();
			const char* pScaleY = elementChild->GetText();
			float scaleY = std::atof(pScaleY);

			game_object.GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(positionX * 32, positionY * 32);
			game_object.GetComponent<ArksEngineComponents::TransformComponent>().SetRotation(rotationX, rotationY);
			game_object.GetComponent<ArksEngineComponents::TransformComponent>().SetScale(scaleX, scaleY);

		}
		else if (componentType == "AlignmentComponent")
		{
			elementChild = elementTag->FirstChildElement();
			const char* pAlignmentType = elementChild->GetText();

			elementChild = elementChild->NextSiblingElement();
			const char* pPositionX = elementChild->GetText();
			float positionX = std::atof(pPositionX);

			elementChild = elementChild->NextSiblingElement();
			const char* pPositionY = elementChild->GetText();
			float positionY = std::atof(pPositionY);

			Alignment alignment;

			// Map the alignment type from the XML text to the enum
			if (std::strcmp(pAlignmentType, "BOTTOM") == 0)
				alignment = BOTTOM;
			else if (std::strcmp(pAlignmentType, "CENTER") == 0)
				alignment = CENTER;
			else if (std::strcmp(pAlignmentType, "TOP") == 0)
				alignment = TOP;
			else if (std::strcmp(pAlignmentType, "LEFT") == 0)
				alignment = LEFT;
			else if (std::strcmp(pAlignmentType, "RIGHT") == 0)
				alignment = RIGHT;
			else if (std::strcmp(pAlignmentType, "TOP_LEFT") == 0)
				alignment = TOP_LEFT;
			else if (std::strcmp(pAlignmentType, "TOP_RIGHT") == 0)
				alignment = TOP_RIGHT;
			else if (std::strcmp(pAlignmentType, "BOTTOM_LEFT") == 0)
				alignment = BOTTOM_LEFT;
			else if (std::strcmp(pAlignmentType, "BOTTOM_RIGHT") == 0)
				alignment = BOTTOM_RIGHT;
			else
				alignment = CENTER;  // Default fallback to CENTER if not found

			
			game_object.AddComponent<ArksEngineComponents::AlignmentComponent>(m_pOwner);
			game_object.GetComponent<ArksEngineComponents::AlignmentComponent>().SetAlignment(alignment);
			game_object.GetComponent<ArksEngineComponents::AlignmentComponent>().SetOffset(positionX, positionY);

		}
		else if (componentType == "SpriteComponent")
		{
			// Get the sprite filename from the XML file
			// and add a SpriteComponent to the entity with that filename
			elementChild = elementTag->FirstChildElement();
			const char* pFileName = elementChild->GetText();

			elementChild = elementChild->NextSiblingElement();
			const char* pNumberOfFrames = elementChild->GetText();
			int frames = atoi(pNumberOfFrames);

			elementChild = elementChild->NextSiblingElement();
			const char* pFrameSpeed = elementChild->GetText();
			int speed = atoi(pFrameSpeed);

			elementChild = elementChild->NextSiblingElement();
			const char* pRValue = elementChild->GetText();
			uint8_t textureColorValue_R = atoi(pRValue);

			elementChild = elementChild->NextSiblingElement();
			const char* pGValue = elementChild->GetText();
			uint8_t textureColorValue_G = atoi(pGValue);

			elementChild = elementChild->NextSiblingElement();
			const char* pBValue = elementChild->GetText();
			uint8_t textureColorValue_B = atoi(pBValue);

			if (frames != 0)
				game_object.AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, pFileName, frames, speed);
			else
				game_object.AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, pFileName);

			
			game_object.GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(textureColorValue_R, textureColorValue_G, textureColorValue_B);

		}
		else if (componentType == "TextUiComponent")
		{
			Token token = Token::No_Token_Req;

			// Get fileName from the XML
			elementChild = elementTag->FirstChildElement();
			const char* pAlignmentType = elementChild ? elementChild->GetText() : nullptr;

			// Get fileName from the XML
			elementChild = elementChild->NextSiblingElement();
			const char* pFileName = elementChild ? elementChild->GetText() : nullptr;
			if (!pFileName)
			{
				pFileName = "";  // Fallback to an empty string if the file name is missing
			}

			// Get FontSize from the XML
			elementChild = elementChild->NextSiblingElement();
			const char* pFontSize = elementChild ? elementChild->GetText() : nullptr;
			int fontSize = 0;  // Default to 0 if font size is missing
			if (pFontSize)
			{
				fontSize = atoi(pFontSize);  // Convert font size string to integer
			}

			elementChild = elementChild->NextSiblingElement();
			const char* pPositionX = elementChild->GetText();
			float positionX = std::atof(pPositionX);

			elementChild = elementChild->NextSiblingElement();
			const char* pPositionY = elementChild->GetText();
			float positionY = std::atof(pPositionY);

			// Get pText from the XML
			elementChild = elementChild->NextSiblingElement();
			const char* pText = elementChild ? elementChild->GetText() : nullptr;

			if (!pText)
			{
				std::cout << "Warning: pText is nullptr!" << std::endl;
				pText = "";  // Fallback to an empty string if the text is missing
			}

			// Use std::string internally to ensure the string data is managed properly
			std::string safeText = pText ? pText : "";


			elementChild = elementChild->NextSiblingElement();
			const char* pTag = elementChild ? elementChild->GetText() : nullptr;

			if (pTag)
			{
				// Use std::string internally to ensure the string data is managed properly
				std::string safeTag = pTag ? pTag : "";

				token = m_pOwner->GetLocalizationManager()->StringToToken(safeTag);
			}

			TextAlignment alignment;

			// Map the alignment type from the XML text to the enum
			if (std::strcmp(pAlignmentType, "BOTTOM") == 0)
				alignment = ALIGN_BOTTOM;
			else if (std::strcmp(pAlignmentType, "CENTER") == 0)
				alignment = ALIGN_CENTER;
			else if (std::strcmp(pAlignmentType, "TOP") == 0)
				alignment = ALIGN_TOP;
			else if (std::strcmp(pAlignmentType, "LEFT") == 0)
				alignment = ALIGN_LEFT;
			else if (std::strcmp(pAlignmentType, "RIGHT") == 0)
				alignment = ALIGN_RIGHT;
			else if (std::strcmp(pAlignmentType, "TOP_LEFT") == 0)
				alignment = ALIGN_TOP_LEFT;
			else if (std::strcmp(pAlignmentType, "TOP_RIGHT") == 0)
				alignment = ALIGN_TOP_RIGHT;
			else if (std::strcmp(pAlignmentType, "BOTTOM_LEFT") == 0)
				alignment = ALIGN_BOTTOM_LEFT;
			else if (std::strcmp(pAlignmentType, "BOTTOM_RIGHT") == 0)
				alignment = ALIGN_BOTTOM_RIGHT;
			else
				alignment = ALIGN_CENTER;  // Default fallback to CENTER if not found

			// Now, safely pass the std::string data converted to const char* to AddComponent
			game_object.AddComponent<ArksEngineComponents::TextUiComponent>(m_pOwner, pFileName, fontSize, safeText.c_str(), token);
			game_object.GetComponent<ArksEngineComponents::TextUiComponent>().SetAlignment(alignment);
			game_object.GetComponent<ArksEngineComponents::TextUiComponent>().SetXOffset(positionX);
			game_object.GetComponent<ArksEngineComponents::TextUiComponent>().SetYOffset(positionY);

		}
		else if (componentType == "ButtonComponent")
		{
			elementChild = elementTag->FirstChildElement();
			const char* pRValue = elementChild->GetText();
			uint8_t buttonHoverColorR = atoi(pRValue);

			elementChild = elementChild->NextSiblingElement();
			const char* pGValue = elementChild->GetText();
			uint8_t buttonHoverColorG = atoi(pGValue);

			elementChild = elementChild->NextSiblingElement();
			const char* pBValue = elementChild->GetText();
			uint8_t buttonHoverColorB = atoi(pBValue);

			game_object.AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
			game_object.GetComponent<ArksEngineComponents::ButtonComponent>().SetButtonHoverColor(buttonHoverColorR, buttonHoverColorG, buttonHoverColorB);
		}
		else if (componentType == "CheckBoxComponent")
		{
			elementChild = elementTag->FirstChildElement();
			const char* pfileName = elementChild->GetText();

			game_object.AddComponent<ArksEngineComponents::CheckBoxComponent>(m_pOwner, pfileName);
		}
		else if (componentType == "ToggleBoxComponent")
		{
			elementChild = elementTag->FirstChildElement();
			const char* pfileName = elementChild->GetText();

			game_object.AddComponent<ArksEngineComponents::ToggleBoxComponent>(m_pOwner, pfileName);
		}
		else if (componentType == "SliderComponent")
		{
			elementChild = elementTag->FirstChildElement();
			const char* pfileName = elementChild->GetText();

			game_object.AddComponent<ArksEngineComponents::SliderComponent>(m_pOwner, pfileName);
		}
		else if (componentType == "InputBoxComponent")
		{
			elementChild = elementTag->FirstChildElement();
			const char* pfileName = elementChild->GetText();

			elementChild = elementChild->NextSiblingElement();
			const char* pFontSize = elementChild ? elementChild->GetText() : nullptr;
			int fontSize = 0;  // Default to 0 if font size is missing
			if (pFontSize)
			{
				fontSize = atoi(pFontSize);  // Convert font size string to integer
			}

			elementChild = elementChild->NextSiblingElement();
			const char* pPositionX = elementChild->GetText();
			float wrapOffsetX = std::atof(pPositionX);

			elementChild = elementChild->NextSiblingElement();
			const char* pPositionY = elementChild->GetText();
			float wrapOffsetY = std::atof(pPositionY);


			game_object.AddComponent<ArksEngineComponents::InputBoxComponent>(m_pOwner, pfileName, fontSize, wrapOffsetX, wrapOffsetY);
		}
		else if (componentType == "ColliderComponent")
		{
			// Get the width, height, and offsets from the XML file
			// and add a ColliderComponent to the entity with those values
			elementChild = elementTag->FirstChildElement();
			const char* pWidth = elementChild->GetText();
			int width = atoi(pWidth);

			elementChild = elementChild->NextSiblingElement();
			const char* pHeight = elementChild->GetText();
			int height = atoi(pHeight);

			elementChild = elementChild->NextSiblingElement();
			const char* pXOffset = elementChild->GetText();
			int xOffset = atoi(pXOffset);

			elementChild = elementChild->NextSiblingElement();
			const char* pYOffset = elementChild->GetText();
			int yOffset = atoi(pYOffset);

			game_object.AddComponent<ArksEngineComponents::ColliderComponent>(m_pOwner->GetRenderer());
			game_object.GetComponent<ArksEngineComponents::ColliderComponent>().SetWidth(width);
			game_object.GetComponent<ArksEngineComponents::ColliderComponent>().SetHeight(height);
			game_object.GetComponent<ArksEngineComponents::ColliderComponent>().SetXOffset(xOffset);
			game_object.GetComponent<ArksEngineComponents::ColliderComponent>().SetYOffset(yOffset);
		}
		else if (componentType == "PhysicsComponent")
		{
			// Get the speed value from the XML file
			// and add a PhysicsComponent to the entity with that value
			elementChild = elementTag->FirstChildElement();
			const char* pSpeed = elementChild->GetText();
			double speed = atoi(pSpeed);

			game_object.AddComponent<ArksEngineComponents::PhysicsComponent>(m_pOwner);
			game_object.GetComponent<ArksEngineComponents::PhysicsComponent>().SetSpeed(speed);
		}
		else if (componentType == "ControllerComponent")
		{
			// Add a ControllerComponent to the entity
			game_object.AddComponent<ArksEngineComponents::ControllerComponent>(m_pOwner->GetInput());
		}
		else if (componentType == "ScriptComponent")
		{
			m_pOwner->GetLuaSystem()->PushGameObject(m_pOwner->GetLuaSystem()->GetLuaState(), &game_object);

			// After you've pushed the GameObject, set it as a global variable in Lua
			m_pOwner->GetLuaSystem()->SetGlobal("GameObject", &game_object);

			game_object.AddComponent<ArksEngineComponents::ScriptComponent>(m_pOwner->GetLuaSystem());

			elementChild = elementTag->FirstChildElement();
			const char* pScript = elementChild->GetText();

			game_object.GetComponent<ArksEngineComponents::ScriptComponent>().AddScript(pScript);

			while (elementChild->NextSiblingElement())
			{
				elementChild = elementTag->NextSiblingElement();
				pScript = elementChild->GetText();
				game_object.GetComponent<ArksEngineComponents::ScriptComponent>().AddScript(pScript);
			}

		}
		else if(componentType == "HealthComponent")
		{
			elementChild = elementTag->FirstChildElement();
			const char* a = elementChild->GetText();
			float maxHealth = std::atof(a);

			elementChild = elementChild->NextSiblingElement();
			const char* b = elementChild->GetText();
			float minHealth = std::atof(b);


			game_object.AddComponent<ArksEngineComponents::HealthComponent>(m_pOwner, maxHealth, minHealth);
		}
		


		// Move to the next sibling element (next component)
		elementTag = elementTag->NextSiblingElement();

	}

	return &game_object;
}
