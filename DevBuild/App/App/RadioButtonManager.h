#pragma once
#include <vector>

namespace ArksEngine
{
	class GameObject;
}

class RadioButtonManager
{
	std::vector<ArksEngine::GameObject*> m_buttons;  // List of buttons to manage
public:
	RadioButtonManager() = default;

	void AddButton(ArksEngine::GameObject* gameObjectWithButtonComponent);

	void SelectButton(ArksEngine::GameObject* button) const;
};

