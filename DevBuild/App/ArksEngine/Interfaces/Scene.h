#pragma once
#include "../Builders/GameObjectBuilder.h"
#include "../Level.h"
#include "../GameObjectManager.h"


// This is a scene interface.


struct SDL_Rect;

namespace ArksEngine
{
	class Music;
	class EventSystem;
	class Core;

	class Scene
	{
		ArksEngine::Core* m_pOwner;
		ArksEngine::GameObjectManager* m_pGameObjectManager;
		ArksEngineBuilders::GameObjectBuilder* m_pGameObjectBuilder;
		ArksEngine::Level* m_pLevel;
		ArksEngine::Music* m_pMusic;
		
	public:
		Scene(ArksEngine::Core* pOwner)
			:m_pOwner(pOwner)
			, m_pGameObjectManager(new ArksEngine::GameObjectManager)
			, m_pGameObjectBuilder(new ArksEngineBuilders::GameObjectBuilder{ m_pOwner, m_pGameObjectManager })
			,m_pLevel(new ArksEngine::Level{m_pOwner, m_pGameObjectManager})
			,m_pMusic(nullptr)
		{
		}

		~Scene()
		{
			delete m_pLevel;
			delete m_pGameObjectBuilder;
			delete m_pGameObjectManager;
		}

		// Initializes the scene
		virtual void Enter() {}

		//Cleans up scene before exit.
		virtual void Exit() {}

		[[nodiscard]] ArksEngine::Core* GetOwner() const { return m_pOwner; }
		[[nodiscard]] GameObjectManager* GetEntityManager() const { return m_pGameObjectManager; }
		[[nodiscard]] Level* Level() const { return m_pLevel; }

		ArksEngine::Music* GetSceneMusic() const { return m_pMusic; }
		void SetSceneMusic(const char* name, int volume, int loop) const;

		// Updates the scene.
		void Update(double deltaTime) const;

		// Loads GameObjects
		GameObject* LoadEntityAndReturn(const char* pXml_File) const;

		void LoadEntity(const char* pXml_File) const;

		// Adds a GameObject to the scene.
		void AddEntity(GameObject* pEntity) const;

		// Renders the scene.
		void Render() const;
	};
}

