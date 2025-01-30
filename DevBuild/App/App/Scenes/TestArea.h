#pragma once
#include "../ArksEngine.h"
#include "../Game.h"

class RadioButtonManager;
enum SupportedLanguages : int;

class TestArea : public ArksEngine::Scene
{

	Game* m_pGame = nullptr;
	RadioButtonManager* radio_buttonGroup1 = nullptr;
	bool isCalculatorActive = false; // Add a state variable to track the toggle state
public:
	TestArea(Game* pOwner);
	~TestArea() = default;


	/**
	 * \brief Enters our scene
	 */
	void Enter() override;


	/**
	 * \brief Exits our scene
	 */
	void Exit() override;


	void ChangeLanguageAndReturnToMainMenu(SupportedLanguages language) const;
};

