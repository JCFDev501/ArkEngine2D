#include "Inventory.h"

#include "ItemContainer.h"
#include "../ArksEngine/Components/TransformComponent.h"

Inventory::Inventory(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}

void Inventory::Init()
{
	m_pTransformRef = &mGameObj->GetComponent<ArksEngineComponents::TransformComponent>();

	BuildInventory();
}

void Inventory::Update(double deltaTime)
{
    // Update all active containers
    for (auto& container : m_ItemContainers)
    {
        if (container && container->IsActive())
        {
            container->Update(deltaTime);
        }
    }

    // Update all active items and remove inactive ones
    m_Items.erase(
        std::remove_if(m_Items.begin(), m_Items.end(),
            [&](Item* item) {
                if (item && item->IsActive())
                {
                    item->Update(deltaTime);
                    item->HandleDragging(m_ItemContainers);
                    return false; // Keep the item in the list
                }
                else
                {
                    delete item; // Clean up memory for inactive items
                    return true; // Remove the item from the list
                }
            }),
        m_Items.end()
    );
}


void Inventory::Render(float xOffset)
{
    // Render all active containers
    for (auto& container : m_ItemContainers)
    {
        if (container && container->IsActive())
        {
            container->Render(xOffset);
        }
    }

    // Render all active items
    for (auto& item : m_Items)
    {
        if (item && item->IsActive())
        {
            item->Render(xOffset);
        }
    }
}


void Inventory::BuildInventory()
{
	BuildContainers();
}

void Inventory::BuildContainers()
{
    const int rows = 4;
    const int cols = 5;
    const float containerWidth = 150.0f;  // Width of each container
    const float containerHeight = 100.0f; // Height of each container
    const float startX = m_pTransformRef->GetPosition().m_x + 50.0f;  // Starting X position
    const float startY = m_pTransformRef->GetPosition().m_y + 50.0f;  // Starting Y position
    const float spacingX = 44.0f;  // Spacing between containers horizontally
    const float spacingY = 40.0f;  // Spacing between containers vertically

    // Loop through rows and columns to build the inventory grid
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            float posX = startX + col * (containerWidth + spacingX);
            float posY = startY + row * (containerHeight + spacingY);

            // Create a new ItemContainer at the calculated position
            ItemContainer* pContainer = new ItemContainer(m_pOwner, posX, posY, containerWidth, containerHeight);

            // Store the container in a collection for later access
            m_ItemContainers.push_back(pContainer);

            // Generate an item in the container for testing purposes
            if (row == 0 && col == 1)
            {
                GenerateItem(pContainer, "Pencil", "/Pencil.png");
            }
            else if(row == 1 && col == 2)
            {
                GenerateItem(pContainer, "Calculator", "/Calculatorinv.png");
            }
            else if (row == 2 && col == 4)
            {
                GenerateItem(pContainer, "Pen", "/Pen.png");
            }
            else if (row == 3 && col == 0)
            {
                GenerateItem(pContainer, "Notebook", "/Notebook.png");
            }
        }
    }

    float posX = startX;
    float posY = startY;

    // Create a new ItemContainer at the calculated position
    ItemContainer* pContainer = new ItemContainer(m_pOwner, posX + 777, posY + 560, containerWidth, containerHeight);

    GenerateItem(pContainer, "TrashCan", "/TrashCan.png");

    // Store the container in a collection for later access
    m_ItemContainers.push_back(pContainer);
}

void Inventory::GenerateItem(ItemContainer* container, const std::string& name, const char* pfile)
{
    const float sizeX = 50.0f; // Item width
    const float sizeY = 75.0f; // Item height

    // Calculate the actual position to center the item in the container
    float centerX = container->GetCenterX() - (sizeX / 2.0f);
    float centerY = container->GetCenterY() - (sizeY / 2.0f);

    // Create the new item
    Item* pItem = new Item(m_pOwner, pfile, centerX, centerY, sizeX, sizeY);
    pItem->SetName(name);

    // Link the item to the container and store it in the inventory's collection
    container->SetItemInSpace(pItem);
    pItem->SetContainerThisItemOwns(container);
    m_Items.push_back(pItem);
}


