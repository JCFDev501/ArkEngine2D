#include "RadioButtonManager.h"

#include "../ArksEngine/GameObject.h"
#include "../ArksEngine/Components/ButtonComponent.h" 
#include "../ArksEngine/Components/CheckBoxComponent.h" 

void RadioButtonManager::AddButton(ArksEngine::GameObject* gameObjectWithButtonComponent)
{
	if (!gameObjectWithButtonComponent->HasComponent<ArksEngineComponents::ButtonComponent>())
		return;

	m_buttons.push_back(gameObjectWithButtonComponent);
}

void RadioButtonManager::SelectButton(ArksEngine::GameObject* button) const
{
	for (auto& abutton : m_buttons)
	{
		if (button == abutton)
		{
			button->GetComponent<ArksEngineComponents::CheckBoxComponent>().SetIsChecked();
			continue;
		}

		abutton->GetComponent<ArksEngineComponents::CheckBoxComponent>().RestButton();
	}

}

// later a a way to get selected button