#include "ItemContainer.h"

#include "../ArksEngine/Components/ButtonComponent.h"
#include "../ArksEngine/Components/SpriteComponent.h"
#include "../ArksEngine/Components/TransformComponent.h"
#include "../ArksEngine/Core.h"
#include "../ArksEngine/Input.h"
#include "../ArksEngine/Utillities/Debug_Log.h"

Item::Item(ArksEngine::Core* pOwner, const char* p_fileName, float posX, float posY, float sizeX, float sizeY)
	:m_pOwner(pOwner)
	,m_PosX(posX)
	,m_PosY(posY)
	,m_SizeX(sizeX)
	,m_SizeY(sizeY)
	,m_p_FileName(p_fileName)
{
	Init();
}

void Item::Init()
{
	// TransformComponent
	this->AddComponent<ArksEngineComponents::TransformComponent>();
	this->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(m_PosX, m_PosY);
	this->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(m_SizeX, m_SizeY);

	// SpriteComponent
	this->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, m_p_FileName);
	this->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(225, 225, 225);

	// ButtonComponent
	this->AddComponent<ArksEngineComponents::ButtonComponent>(m_pOwner);
	this->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void  // Give the button some logic
		{
			if (this->GetName() != "TrashCan")
				itemClicked = true;
		});
}

void Item::HandleDragging(std::vector<ItemContainer*> m_ItemContainers)
{
	static float offsetX = 0.0f; // Offset between the item's position and the mouse click
	static float offsetY = 0.0f;

	if (itemClicked)
	{
		if (m_pOwner->GetInput()->IsKeyHeld(ArksEngine::Input::Left_Click))
		{
			// If dragging just started, calculate the offset
			if (offsetX == 0.0f && offsetY == 0.0f)
			{
				float itemPosX = this->GetComponent<ArksEngineComponents::TransformComponent>().GetPosition().m_x;
				float itemPosY = this->GetComponent<ArksEngineComponents::TransformComponent>().GetPosition().m_y;

				// Calculate offset relative to where the item was clicked
				offsetX = itemPosX - m_pOwner->GetInput()->GetMouseClickLocation().m_x;
				offsetY = itemPosY - m_pOwner->GetInput()->GetMouseClickLocation().m_y;
			}

			// Update the item's position relative to the current mouse hover location and the offset
			this->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(
				m_pOwner->GetInput()->GetMouseHoverLocation().m_x + offsetX,
				m_pOwner->GetInput()->GetMouseHoverLocation().m_y + offsetY
			);
		}
		else
		{

			for (auto container : m_ItemContainers)
			{
				if (container != m_pContainerThisItemOwns && container->GetItemInSpace() == nullptr)
				{
					// Determine if the mouse pointer is within the container's bounds
					float mouseX = m_pOwner->GetInput()->GetMouseHoverLocation().m_x;
					float mouseY = m_pOwner->GetInput()->GetMouseHoverLocation().m_y;
					ArksEngineComponents::TransformComponent TC = container->GetComponent<ArksEngineComponents::TransformComponent>();

					if (mouseX >= TC.GetPosition().m_x &&
						mouseX <= TC.GetPosition().m_x + TC.GetScale().m_x &&
						mouseY >= TC.GetPosition().m_y &&
						mouseY <= TC.GetPosition().m_y + TC.GetScale().m_y)
					{
						// Center the item in this container
						float centerX = container->GetCenterX() - (m_SizeX / 2.0f);
						float centerY = container->GetCenterY() - (m_SizeY / 2.0f);

						this->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(centerX, centerY);
						container->SetItemInSpace(this); // Assign this item to the container

						m_pContainerThisItemOwns->SetItemInSpace(nullptr);

						m_pContainerThisItemOwns = container;
						break;
					}
				}
				else if (container != m_pContainerThisItemOwns && container->GetItemInSpace()->GetName() == "TrashCan")
				{
					// Determine if the mouse pointer is within the container's bounds
					float mouseX = m_pOwner->GetInput()->GetMouseHoverLocation().m_x;
					float mouseY = m_pOwner->GetInput()->GetMouseHoverLocation().m_y;
					ArksEngineComponents::TransformComponent TC = container->GetComponent<ArksEngineComponents::TransformComponent>();

					if (mouseX >= TC.GetPosition().m_x &&
						mouseX <= TC.GetPosition().m_x + TC.GetScale().m_x &&
						mouseY >= TC.GetPosition().m_y &&
						mouseY <= TC.GetPosition().m_y + TC.GetScale().m_y)
					{

						m_pContainerThisItemOwns->SetItemInSpace(nullptr);
						m_pContainerThisItemOwns = nullptr;
						this->SetActive(false);

						break;
					}
				}
			}

			// Reset dragging state and center the item in its container
			const float sizeX = m_SizeX; // Item width
			const float sizeY = m_SizeY; // Item height

			// Calculate the actual position to center the item in the container
			if (m_pContainerThisItemOwns)
			{
				float centerX = m_pContainerThisItemOwns->GetCenterX() - (sizeX / 2.0f);
				float centerY = m_pContainerThisItemOwns->GetCenterY() - (sizeY / 2.0f);

				this->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(centerX, centerY);
			}
			
			

			// Reset dragging state
			itemClicked = false;
			offsetX = 0.0f; // Reset offset
			offsetY = 0.0f;
		}
	}
}



ItemContainer::ItemContainer(ArksEngine::Core* pOwner, float posX, float posY, float sizeX, float sizeY)
	:m_pOwner(pOwner)
	,m_PosX(posX)
	,m_PosY(posY)
	,m_SizeX(sizeX)
	,m_SizeY(sizeY)
{
	Init();
}

void ItemContainer::Init()
{
	// TransformComponent
	this->AddComponent<ArksEngineComponents::TransformComponent>();
	this->GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(m_PosX, m_PosY);
	this->GetComponent<ArksEngineComponents::TransformComponent>().SetScale(m_SizeX, m_SizeY);

	this->AddComponent<ArksEngineComponents::SpriteComponent>(m_pOwner, "/InventorySlot.png");
	this->GetComponent<ArksEngineComponents::SpriteComponent>().SetTextureColor(225, 225, 225);

	// Determine center pos based off of Transform scale and Position
	float centerX = m_PosX + m_SizeX / 2.0f;
	float centerY = m_PosY + m_SizeY / 2.0f;

	m_CenterX = centerX;
	m_CenterY = centerY;
}
