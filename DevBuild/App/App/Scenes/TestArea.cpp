#include "TestArea.h"

#include <chrono>
#include <thread>

#include "../calculator.h"
#include "../../ArksEngine/Components/CheckBoxComponent.h"
#include "../../ArksEngine/Components/ToggleBoxComponent.h"
#include "../RadioButtonManager.h"
#include "../../ArksEngine/Components/InputBoxComponent.h"
#include "../game.h"
#include "../GameManager.h"
#include "../Inventory.h"
#include "../../ArksEngine/Components/ScrollBoxComponent.h"


TestArea::TestArea(Game* pOwner)
	:Scene(pOwner)
	,m_pGame(pOwner)
{
}

void TestArea::Enter()
{


	// -------------------------------------------------------- Main Menu -------------------------------------------------------------
	LoadEntity("MainMenuBackground.xml");

	ArksEngine::GameObject* calculatorBtn = LoadEntityAndReturn("CalculatorBtn.xml");
	calculatorBtn->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			// Toggle the state
			isCalculatorActive = !isCalculatorActive;

			// Log the current state
			GetOwner()->GetDebug_Log()->Log(isCalculatorActive ? "Calculator Activated" : "Calculator Deactivated");

			// Set the active state of the "Calculator" based on the toggle
			GetEntityManager()->SetGameObjActiveBasedOffTag("Calculator", isCalculatorActive);
		});

	LoadEntity("PlayButton.xml");
	ArksEngine::GameObject* playButton = GetEntityManager()->GetGameObject("PlayButton");
	playButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the Play Button");
			GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", false);

			// Start a timer to delay activation of "CharacterSelect"
			std::thread([this]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Delay for 1 second
					GetEntityManager()->SetGameObjActiveBasedOffTag("CharacterSelect", true);
				}).detach();
		});

	LoadEntity("OptionsButton.xml");
	ArksEngine::GameObject* optionsButton = GetEntityManager()->GetGameObject("OptionsButton");
	optionsButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the Options Button");
			GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", false);
			GetEntityManager()->SetGameObjActiveBasedOffTag("Options Menu", true);
		});

	LoadEntity("QuitButton.xml");
	ArksEngine::GameObject* quitButton = GetEntityManager()->GetGameObject("QuitButton");
	quitButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the Quit Button");
			GetOwner()->SetQuit(true);
		});

	LoadEntity("SongsBtn.xml");
	ArksEngine::GameObject* songsButton = GetEntityManager()->GetGameObject("SongsBtn");
	songsButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the Songs Button");
			GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", false);

			// Start a timer to delay activation of "CharacterSelect"
			std::thread([this]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Delay for 1 second
					GetEntityManager()->SetGameObjActiveBasedOffTag("Songs Menu", true);
				}).detach();
		});

	LoadEntity("LanguageButton.xml");
	ArksEngine::GameObject* languageButton = GetEntityManager()->GetGameObject("LanguageButton");
	languageButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the Language Button");
			GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", false);
			GetEntityManager()->SetGameObjActiveBasedOffTag("Language Menu", true);

		});

	LoadEntity("InputButton.xml");
	ArksEngine::GameObject* inputButton = GetEntityManager()->GetGameObject("InputButton");
	inputButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the Input Button");
			GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", false);
			GetEntityManager()->SetGameObjActiveBasedOffTag("Input Menu", true);
		});

	// ---------------------------------------------------------------- iNVENTORY ----------------------------------------------------
	ArksEngine::GameObject* inventorybttn = LoadEntityAndReturn("InventoryButton.xml");
	inventorybttn->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void  // Give the button some logic
		{
			GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", false);
			GetEntityManager()->SetGameObjActiveBasedOffTag("Inventory Menu", true);
		});


	ArksEngine::GameObject* inventory = LoadEntityAndReturn("Inventory.xml");
	inventory->AddComponent<Inventory>(GetOwner());

	ArksEngine::GameObject* inventoryBackBttn = LoadEntityAndReturn("InventoryBackBttn.xml");
	inventoryBackBttn->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void  // Give the button some logic
	{
		GetEntityManager()->SetGameObjActiveBasedOffTag("Inventory Menu", false);
		GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);
	});

	// ---------------------------------------------------------------- cALCULATOR ----------------------------------------------------
	ArksEngine::GameObject* calculator = LoadEntityAndReturn("Calculator.xml");
	calculator->AddComponent<Calculator>(GetOwner(), "Assets/comicbd.ttf", 20);

	

	// --------------------------------------------------------- Songs Menu --------------------------------------------------------
	LoadEntity("SongsBackground.xml");

	ArksEngine::GameObject& game_object(GetEntityManager()->AddGameObject());
	game_object.SetName("Songs Scroll");
	game_object.SetTag("Songs Menu");
	game_object.SetActive(false);
	game_object.GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(0, 0);
	game_object.GetComponent<ArksEngineComponents::TransformComponent>().SetScale(400, 768);
	game_object.AddComponent<ArksEngineComponents::AlignmentComponent>(GetOwner());
	game_object.GetComponent<ArksEngineComponents::AlignmentComponent>().SetAlignment(Alignment::RIGHT);
	game_object.AddComponent<ArksEngineComponents::ColliderComponent>(GetOwner()->GetRenderer());
	game_object.GetComponent<ArksEngineComponents::ColliderComponent>().SetWidth(400);
	game_object.GetComponent<ArksEngineComponents::ColliderComponent>().SetHeight(768);
	game_object.AddComponent<ArksEngineComponents::ScrollBoxComponent>(GetOwner());
	game_object.GetComponent<ArksEngineComponents::ScrollBoxComponent>().CreateNumAmoutOfButtons(24);

	LoadEntity("SongsBackBtn.xml");
	ArksEngine::GameObject* songsBtnButton = GetEntityManager()->GetGameObject("SongsBackBtn");
	songsBtnButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the Back Button");
			GetEntityManager()->SetGameObjActiveBasedOffTag("Songs Menu", false);
			GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);
		});

	// --------------------------------------------------------- Ready Menu --------------------------------------------------------
	LoadEntity("ReadyMenu.xml");
	ArksEngine::GameObject* readyBackButton = LoadEntityAndReturn("ReadyBackButton.xml");
	readyBackButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the ReadyBackButton");
			GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", false);
			GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", true);

			// Start a timer to delay activation of "CharacterSelect"
			std::thread([this]()
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Delay for 1 second
					if (m_pGame->GetGameManager()->SamCharacterSelected())
					{
						GetEntityManager()->SetGameObjActiveBasedOffTag("SamOutfitSelect", true);
						GetEntityManager()->SetGameObjActiveBasedOffTag("SamSelected", false);
					}
					else if (m_pGame->GetGameManager()->MaxCharacterSelected())
					{
						GetEntityManager()->SetGameObjActiveBasedOffTag("MaxOutfitSelect", true);
						GetEntityManager()->SetGameObjActiveBasedOffTag("MaxSelected", false);
					}
				}).detach();
		});

	ArksEngine::GameObject* readyPlayButton = LoadEntityAndReturn("ReadyPlayButton.xml");
	readyPlayButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
		{
			GetOwner()->GetDebug_Log()->Log("You Clicked the ReadyPlayButton");
			GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", false);
			m_pGame->LoadScene(Game::GameLevel);
		});


			// -------------------------------------------------------- Language Menu -------------------------------------------------------------
			LoadEntity("LanguageBackground.xml");

			LoadEntity("AmericaLanguageButton.xml");
			ArksEngine::GameObject* americaButton = GetEntityManager()->GetGameObject("AmericaLanguageButton");
			americaButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the AmericaLanguageButton");
					ChangeLanguageAndReturnToMainMenu(SupportedLanguages::English);
				});

			LoadEntity("FranceLanguageButton.xml");
			ArksEngine::GameObject* franceButton = GetEntityManager()->GetGameObject("FranceLanguageButton");
			franceButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the FranceLanguageButton");
					ChangeLanguageAndReturnToMainMenu(SupportedLanguages::French);
				});

			LoadEntity("ItalyLanguageButton.xml");
			ArksEngine::GameObject* italyButton = GetEntityManager()->GetGameObject("ItalyLanguageButton");
			italyButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the ItalyLanguageButton");
					ChangeLanguageAndReturnToMainMenu(SupportedLanguages::Italian);
				});

			LoadEntity("GermanLanguageButton.xml");
			ArksEngine::GameObject* germanButton = GetEntityManager()->GetGameObject("GermanLanguageButton");
			germanButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the GermanLanguageButton");
					ChangeLanguageAndReturnToMainMenu(SupportedLanguages::German);
				});

			LoadEntity("SpainLanguageButton.xml");
			ArksEngine::GameObject* spainButton = GetEntityManager()->GetGameObject("SpainLanguageButton");
			spainButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the SpainLanguageButton");
					ChangeLanguageAndReturnToMainMenu(SupportedLanguages::Spanish);
				});

			// -------------------------------------------------------- Options Menu -------------------------------------------------------------
			LoadEntity("OptionsMenuScreenBackground.xml");

			LoadEntity("DifficultyButton.xml");
			ArksEngine::GameObject* difficultyButton = GetEntityManager()->GetGameObject("DifficultyButton");
			difficultyButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Difficulty Button");
					GetEntityManager()->SetGameObjActiveBasedOffTag("Difficulty Menu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("Options Menu", false);
				});

			LoadEntity("VolumeButton.xml");
			ArksEngine::GameObject* VolumeButton = GetEntityManager()->GetGameObject("VolumeButton");
			VolumeButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Volume Button");
					GetEntityManager()->SetGameObjActiveBasedOffTag("Volume Menu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("Options Menu", false);
				});

			LoadEntity("BackButton.xml");
			ArksEngine::GameObject* backButton = GetEntityManager()->GetGameObject("BackButton");
			backButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Back Button");
					GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("Options Menu", false);

				});

			// -------------------------------------------------------- Difficulty Menu -------------------------------------------------------------
			LoadEntity("DifficultyMenuScreenBackground.xml");

			LoadEntity("HintCheckBox.xml");
			ArksEngine::GameObject* HintCheckBoxButton = GetEntityManager()->GetGameObject("HintCheckBoxButton");
			HintCheckBoxButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, HintCheckBoxButton]() -> void
				{
					HintCheckBoxButton->GetComponent<ArksEngineComponents::CheckBoxComponent>().SetIsChecked();
				});

			LoadEntity("Permadeath_RespawnToggleButton.xml");
			ArksEngine::GameObject* PermadeathToggle = GetEntityManager()->GetGameObject("PermadeathRespawnToggleButton");
			PermadeathToggle->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, PermadeathToggle]() -> void
				{
					PermadeathToggle->GetComponent<ArksEngineComponents::ToggleBoxComponent>().Toggle();
				});


			radio_buttonGroup1 = new RadioButtonManager;

			// Load the button entity
			LoadEntity("EasyButton.xml");
			ArksEngine::GameObject* easyButton = GetEntityManager()->GetGameObject("EasyButton");
			radio_buttonGroup1->AddButton(easyButton);
			easyButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, easyButton]() -> void
				{
					// Ensure this button gets selected in the radio group
					radio_buttonGroup1->SelectButton(easyButton);
				});

			LoadEntity("NormalButton.xml");
			ArksEngine::GameObject* NormalButton = GetEntityManager()->GetGameObject("NormalButton");
			radio_buttonGroup1->AddButton(NormalButton);
			NormalButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, NormalButton]() -> void
				{
					// Ensure this button gets selected in the radio group
					radio_buttonGroup1->SelectButton(NormalButton);
				});

			LoadEntity("HardButton.xml");
			ArksEngine::GameObject* HardButton = GetEntityManager()->GetGameObject("HardButton");
			radio_buttonGroup1->AddButton(HardButton);
			HardButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, HardButton]() -> void
				{
					// Ensure this button gets selected in the radio group
					radio_buttonGroup1->SelectButton(HardButton);
				});

			LoadEntity("DifficultyBackButton.xml");
			ArksEngine::GameObject* difficultyBackButton = GetEntityManager()->GetGameObject("DifficultyBackButton");
			difficultyBackButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Back Button");
					GetEntityManager()->SetGameObjActiveBasedOffTag("Options Menu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("Difficulty Menu", false);

				});



			// -------------------------------------------------------- Volume Menu -------------------------------------------------------------
			LoadEntity("VolumeMenuScreenBackGround.xml");


			LoadEntity("MuteCheckBox.xml");
			ArksEngine::GameObject* MuteCheckBoxButton = GetEntityManager()->GetGameObject("MuteCheckBoxButton");
			MuteCheckBoxButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, MuteCheckBoxButton]() -> void
				{
					MuteCheckBoxButton->GetComponent<ArksEngineComponents::CheckBoxComponent>().SetIsChecked();
				});


			LoadEntity("MonoStereoToggleButton.xml");
			ArksEngine::GameObject* MonoStereoToggleButton = GetEntityManager()->GetGameObject("MonoStereoToggleButton");
			MonoStereoToggleButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, MonoStereoToggleButton]() -> void
				{
					MonoStereoToggleButton->GetComponent<ArksEngineComponents::ToggleBoxComponent>().Toggle();
				});


			LoadEntity("SliderBar1.xml");
			LoadEntity("SliderBar2.xml");
			LoadEntity("SliderBar3.xml");


			LoadEntity("VolumeBackButton.xml");
			ArksEngine::GameObject* volumeBackButton = GetEntityManager()->GetGameObject("VolumeBackButton");
			volumeBackButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Back Button");
					GetEntityManager()->SetGameObjActiveBasedOffTag("Options Menu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("Volume Menu", false);
				});

			// -------------------------------------------------------- Input Menu -------------------------------------------------------------
			LoadEntity("InputScreenBackground.xml");

			LoadEntity("InputPaper.xml");
			ArksEngine::GameObject* InputPaper = GetEntityManager()->GetGameObject("InputPaper");

			LoadEntity("InputBackButton.xml");
			ArksEngine::GameObject* InputBackButton = GetEntityManager()->GetGameObject("InputBackButton");
			InputBackButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, InputPaper]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Input Back Button");
					GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);

					InputPaper->GetComponent<ArksEngineComponents::InputBoxComponent>().ExitMenu();

					GetEntityManager()->SetGameObjActiveBasedOffTag("Input Menu", false);

				});


			if (m_pGame->GetGameManager()->IsFirstTimeBootedUp())
			{
				// -------------------------------------------------------- Start Menu -------------------------------------------------------------
				LoadEntity("Background.xml"); // Create our game obj from a xml file

				LoadEntity("StartButton.xml");
				ArksEngine::GameObject* startButton = GetEntityManager()->GetGameObject("StartButton");
				startButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void  // Give the button some logic
					{
						GetOwner()->GetDebug_Log()->Log("You Clicked the Start Button");
						GetEntityManager()->SetGameObjActiveBasedOffTag("Start Menu", false);
						m_pGame->GetGameManager()->SetFirstTimeBootedUp(false);

						// Start a timer to delay activation of "CharacterSelect"
						std::thread([this]()
							{
								std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Delay for 1 second
								GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);
							}).detach();
					});

			}
			else
			{
				GetEntityManager()->SetGameObjActiveBasedOffTag("Start Menu", false);
				GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);
			}

			// --------------------------------------------------------- Character Selection --------------------------------------------------------
			LoadEntity("CharacterSelectBackground.xml");

			ArksEngine::GameObject* samCharacterSelect = LoadEntityAndReturn("SamCharacterSelect.xml");
			ArksEngine::GameObject* sam = LoadEntityAndReturn("Sam.xml");
			samCharacterSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, sam]() -> void
				{

					GetOwner()->GetDebug_Log()->Log("You Clicked the Sam Character Select Button");
					m_pGame->GetGameManager()->SetSamCharacterSelected(true);
					m_pGame->GetGameManager()->SetMaxCharacterSelected(false);
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("SamDuster", "../../App/Assets/SamDuster.png");
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("SamPajamas", "../../App/Assets/SamPajamas.png");
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("SamScrubs", "../../App/Assets/SamScrubs.png");
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("SamTuxedo", "../../App/Assets/SamTuxedo.png");

					GetEntityManager()->SetGameObjActiveBasedOffTag("CharacterSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", true);

					// Start a timer to delay activation of "CharacterSelect"
					std::thread([this]()
						{
							std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Delay for 1 second
							GetEntityManager()->SetGameObjActiveBasedOffTag("SamOutfitSelect", true);
						}).detach();



				});


			ArksEngine::GameObject* maxCharacterSelect = LoadEntityAndReturn("MaxCharacterSelect.xml");
			ArksEngine::GameObject* max = LoadEntityAndReturn("Max.xml");
			maxCharacterSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, max]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Max Character Select Button");
					m_pGame->GetGameManager()->SetMaxCharacterSelected(true);
					m_pGame->GetGameManager()->SetSamCharacterSelected(false);
					max->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("MaxPajamas", "../../App/Assets/MaxPajamas.png");
					max->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("MaxWedding", "../../App/Assets/MaxWedding.png");
					max->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("MaxBoyscout", "../../App/Assets/MaxBoyscout.png");
					max->GetComponent<ArksEngineComponents::SpriteComponent>().AddTexture("MaxOpera", "../../App/Assets/MaxOpera.png");

					GetEntityManager()->SetGameObjActiveBasedOffTag("CharacterSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", true);


					// Start a timer to delay activation of "CharacterSelect"
					std::thread([this]()
						{
							std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Delay for 1 second
							GetEntityManager()->SetGameObjActiveBasedOffTag("MaxOutfitSelect", true);
						}).detach();

				});


			ArksEngine::GameObject* characterSelectBackButton = LoadEntityAndReturn("SelectCharacterBackButton.xml");
			characterSelectBackButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Character Select Back Button");
					GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("CharacterSelect", false);
				});

			// --------------------------------------------------------- Outfit Selection --------------------------------------------------------
			LoadEntity("OutfitSelectBackground.xml");

			ArksEngine::GameObject* outfitSelectBackButton = LoadEntityAndReturn("SelectOutfitBackButton.xml");
			outfitSelectBackButton->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Outfit Select Back Button");
					
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);

					if (m_pGame->GetGameManager()->SamCharacterSelected())
					{
						GetEntityManager()->SetGameObjActiveBasedOffTag("SamOutfitSelect", false);
					}
					else if (m_pGame->GetGameManager()->MaxCharacterSelected())
					{
						GetEntityManager()->SetGameObjActiveBasedOffTag("MaxOutfitSelect", false);
					}

					// Start a timer to delay activation of "CharacterSelect"
					std::thread([this]()
						{
							std::this_thread::sleep_for(std::chrono::milliseconds(350)); // Delay for 1 second
							GetEntityManager()->SetGameObjActiveBasedOffTag("CharacterSelect", true);
							
						}).detach();
				});


			// --------------------------------------------------------- Sam Outfit Selection --------------------------------------------------------
			ArksEngine::GameObject* samPajamasSelect = LoadEntityAndReturn("SamPajamas.xml");
			samPajamasSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, sam]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Sam Pajamas Select Button");
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("SamPajamas");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamSelected", true);

				});

			ArksEngine::GameObject* samTuxedoSelect = LoadEntityAndReturn("SamTuxedo.xml");
			samTuxedoSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, sam]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Sam Tuxedo Select Button");
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("SamTuxedo");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamSelected", true);

				});

			ArksEngine::GameObject* samScrubsSelect = LoadEntityAndReturn("SamScrubs.xml");
			samScrubsSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, sam]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Sam Scrubs Select Button");
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("SamScrubs");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamSelected", true);

				});

			ArksEngine::GameObject* samDusterSelect = LoadEntityAndReturn("SamDuster.xml");
			samDusterSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, sam]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Sam Duster Select Button");
					sam->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("SamDuster");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("SamSelected", true);

				});

			// --------------------------------------------------------- Max Outfit Selection --------------------------------------------------------
			ArksEngine::GameObject* maxPajamasSelect = LoadEntityAndReturn("MaxPajamas.xml");
			maxPajamasSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, max]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Max Pajamas Select Button");
					max->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("MaxPajamas");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxSelected", true);

				});

			ArksEngine::GameObject* maxBoyscoutSelect = LoadEntityAndReturn("MaxBoyscout.xml");
			maxBoyscoutSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, max]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Max Boyscout Select Button");
					max->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("MaxBoyscout");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxSelected", true);

				});

			ArksEngine::GameObject* maxOperaSelect = LoadEntityAndReturn("MaxOpera.xml");
			maxOperaSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, max]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Max Opera Select Button");
					max->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("MaxOpera");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxSelected", true);

				});

			ArksEngine::GameObject* maxWeddingSelect = LoadEntityAndReturn("MaxWedding.xml");
			maxWeddingSelect->GetComponent<ArksEngineComponents::ButtonComponent>().OnClick([this, max]() -> void
				{
					GetOwner()->GetDebug_Log()->Log("You Clicked the Max Wedding Select Button");
					max->GetComponent<ArksEngineComponents::SpriteComponent>().SwitchTexture("MaxWedding");
					GetEntityManager()->SetGameObjActiveBasedOffTag("OutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxOutfitSelect", false);
					GetEntityManager()->SetGameObjActiveBasedOffTag("ReadyMenu", true);
					GetEntityManager()->SetGameObjActiveBasedOffTag("MaxSelected", true);

				});
}

void TestArea::Exit()
{
	delete radio_buttonGroup1;
}

void TestArea::ChangeLanguageAndReturnToMainMenu(SupportedLanguages language) const
{

	GetOwner()->GetLocalizationManager()->SetCurrentLanguage(language);
	GetEntityManager()->SetGameObjActiveBasedOffTag("Language Menu", false);
	GetEntityManager()->SetGameObjActiveBasedOffTag("Main Menu", true);
}
