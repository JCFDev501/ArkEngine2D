#include "SceneManager.h"
#include "Interfaces/Scene.h"

ArksEngine::SceneManager::SceneManager(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
	, m_pCurrentScene(nullptr)
	, m_pNextScene(nullptr)
{
}

ArksEngine::SceneManager::~SceneManager()
{
	// exit the current state.
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->Exit();
	}

	// delete the current state
	delete m_pCurrentScene;
}

void ArksEngine::SceneManager::UpdateCurrentScene(double deltaTime)
{
    // Perform actual state change if a new scene is queued
    if (m_pNextScene != nullptr)
    {
        // Exit and delete the current scene if it exists
        if (m_pCurrentScene != nullptr)
        {
            m_pCurrentScene->Exit();
            delete m_pCurrentScene;
        }

        // Switch to the queued scene
        m_pCurrentScene = m_pNextScene;
        m_pNextScene = nullptr;

        // Enter the new scene
        if (m_pCurrentScene != nullptr)
        {
            m_pCurrentScene->Enter();
        }
    }

    // If the current scene is not null, call Update.
    if (m_pCurrentScene != nullptr)
    {
        m_pCurrentScene->Update(deltaTime);
    }
}

void ArksEngine::SceneManager::RenderCurrentScene() const
{
	// If My current state is not null call Render.
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->Render();
	}
}

void ArksEngine::SceneManager::ChangeScene(Scene* pNewScene)
{
	// Queue the scene change
	m_pNextScene = pNewScene;
}
