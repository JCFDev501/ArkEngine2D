#pragma once
#include "../ArksEngine/GameObject.h"

class ItemContainer;

namespace ArksEngine
{
	class Core;
}

class Item : public ArksEngine::GameObject
{
	ItemContainer* m_pContainerThisItemOwns = nullptr;

	// A pointer to the Core class
	ArksEngine::Core* m_pOwner = nullptr;

	float m_PosX, m_PosY;
	float m_SizeX, m_SizeY;

	const char* m_p_FileName;

	bool itemClicked = false;

public:
	Item(ArksEngine::Core* pOwner, const char* p_fileName, float posX, float posY, float sizeX, float sizeY);

	void Init();

	void HandleDragging(std::vector<ItemContainer*> m_ItemContainers);

	void SetContainerThisItemOwns(ItemContainer* container) { m_pContainerThisItemOwns = container; }
};

class ItemContainer : public ArksEngine::GameObject
{
	// A pointer to the Core class
	ArksEngine::Core* m_pOwner = nullptr;

	bool m_SpaceFree = true;
	Item* m_pItemInSpace = nullptr;

	float m_PosX, m_PosY;
	float m_SizeX, m_SizeY;

	float m_CenterX = 0;
	float m_CenterY = 0;
public:
	ItemContainer(ArksEngine::Core* pOwner, float posX, float posY, float sizeX, float sizeY);

	void Init();

	float GetCenterX() const { return m_CenterX; }
	float GetCenterY() const { return m_CenterY; }

	void SetItemInSpace(Item* pItemInSpace) { m_pItemInSpace = pItemInSpace; }
	Item* GetItemInSpace() const { return m_pItemInSpace; }

};

