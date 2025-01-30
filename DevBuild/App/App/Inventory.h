#pragma once
#include <string>
#include <vector>

#include "../ArksEngine/Components/Component.h"

class Item;
class ItemContainer;

namespace ArksEngineComponents
{
	class TransformComponent;
}

namespace ArksEngine
{
	class Core;
}

class Inventory : public ArksEngineComponents::Component
{
	// A pointer to the Core class
	ArksEngine::Core* m_pOwner = nullptr;

	// A pointer to the TransformComponent class
	ArksEngineComponents::TransformComponent* m_pTransformRef = nullptr;

	// List of item containers
	std::vector<ItemContainer*> m_ItemContainers;

	// List of Items
	std::vector<Item*> m_Items;

	// Selected Item
	Item* m_SelectedItem = nullptr;
public:
	Inventory(ArksEngine::Core* pOwner);

	void Init() override;
	void Update(double deltaTime) override;
	void Render(float xOffset) override;
	void BuildInventory();
	void BuildContainers();
	void GenerateItem(ItemContainer* container, const std::string& name, const char* pfile);
};



