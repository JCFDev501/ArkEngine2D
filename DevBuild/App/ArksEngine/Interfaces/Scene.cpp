#include "Scene.h"
#include "../Core.h"
#include "../Music.h"
#include "../PhysicsSystem.h"
#include "../Renderer.h"
#include "../Window.h"
#include "../Components/TransformComponent.h"
#include "../GameObject.h"
#include "../Components/HealthComponent.h"
#include "../Utillities/Debug_Log.h"

namespace ArksEngineComponents
{
	class HealthComponent;
	class TransformComponent;
}

void ArksEngine::Scene::SetSceneMusic(const char* name, int volume, int loop) const
{
	ArksEngine::Music music{ GetOwner(), name };
	music.Load_Music();
	music.Set_MusicVolume(100);
	music.Play_Music(0);
}

void ArksEngine::Scene::Update(double deltaTime) const
{
	m_pGameObjectManager->Update(deltaTime);

    m_pGameObjectManager->Refresh();

	GetOwner()->GetPhysicsSystem()->CheckCollision(m_pGameObjectManager);
}

ArksEngine::GameObject* ArksEngine::Scene::LoadEntityAndReturn(const char* pXml_File) const
{
	return m_pGameObjectBuilder->CreateGameObject(pXml_File);
}

void ArksEngine::Scene::LoadEntity(const char* pXml_File) const
{
	m_pGameObjectBuilder->CreateGameObject(pXml_File);
}

void ArksEngine::Scene::AddEntity(GameObject* pEntity) const
{
	m_pGameObjectManager->AddGameObject();
}

void ArksEngine::Scene::Render() const
{
    GetOwner()->GetRenderer()->SetRenderDrawColor(225, 225, 225, 225);
    GetOwner()->GetRenderer()->ClearScreen();

    // Get the entity you want to follow.
    //const GameObject* followedEntity = GetEntityManager()->GetGameObject("RedWanderer");
    //
    //// Get the followed entity's position.
    //const float playerXPos = followedEntity->GetComponent<ArksEngineComponents::TransformComponent>().GetPosition().m_x;
    //
    //// Calculate the desired x-position of the player on the screen.
    //const int screenWidth = GetOwner()->GetWindow()->GetScreenWidth();
    //const float desiredPlayerScreenXPos = screenWidth * 0.5;
    //
    //// Calculate the x-offset for level rendering based on the entity's position.
    //const float levelRenderXOffset = desiredPlayerScreenXPos - playerXPos;
    //
    //float actualXOffSet = levelRenderXOffset;
    //
    //// Check if the entity exists.
    //if (followedEntity)
    //{
    //    // Calculate the maximum x-offset before scrolling should stop.
    //    const float maxScrollXOffset = static_cast<float>(m_pOwner->GetWindow()->GetScreenWidth()) - static_cast<float>(m_pOwner->GetWindow()->GetScreenWidth());
    //    const float minScrollXOffset = 1600 * -1;
    //
    //
    //    // Calculate the current x-offset for level rendering based on the entity's position.
    //    float levelRenderXOffset = desiredPlayerScreenXPos - playerXPos;
    //
    //    // Check if the current x-offset exceeds the maximum x-offset.
    //    if (levelRenderXOffset > maxScrollXOffset)
    //    {
    //        // Set the x-offset to the maximum value to stop scrolling.
    //        levelRenderXOffset = maxScrollXOffset;
    //    }
    //    // Check if the current x-offset exceeds the maximum x-offset.
    //    else if (minScrollXOffset > levelRenderXOffset  )
    //    {
    //        // Set the x-offset to the maximum value to stop scrolling.
    //        levelRenderXOffset = minScrollXOffset;
    //    }
    //
    //    // Render the level using the calculated x-offset.
    //    m_pLevel->Render(static_cast<int>(levelRenderXOffset), 0);
    //
    //    // Render entities with the same x-offset.
    //    m_pGameObjectManager->Render(levelRenderXOffset);
    //}


    if (m_pLevel)
		m_pLevel->Render();

    m_pGameObjectManager->Render();

    GetOwner()->GetRenderer()->RenderPresent();
}
