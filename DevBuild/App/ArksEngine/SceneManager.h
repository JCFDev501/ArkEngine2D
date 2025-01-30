#pragma once
// This is a interface that will manage all of the scenes

namespace ArksEngine
{
	class Scene;
	class Core;

	class SceneManager
	{
		ArksEngine::Core* m_pOwner; // This is a Ptr to the core

		ArksEngine::Scene* m_pCurrentScene; // This is a Ptr to the a current scene

		ArksEngine::Scene* m_pNextScene; // This is a Ptr to the next scene
	public:
		/**
		 * \brief This is a constructor for the scene manager 
		 * \param pOwner This is a Ptr to the core
		 */
		SceneManager(ArksEngine::Core* pOwner);

		/**
		 * \brief This is a de-constructor
		 */
		~SceneManager();

		// Update the current game state.
		void UpdateCurrentScene(double deltaTime);

		// Render the current game state.
		void RenderCurrentScene() const;

		// Handle the given event within the current state.
		//virtual bool HandleEvent(SDL_Event* pEvent) = 0;

		//Exits current state and enters new state
		void ChangeScene(Scene* pNewScene);
	};
}




