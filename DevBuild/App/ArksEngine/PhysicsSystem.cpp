#include "PhysicsSystem.h"
#include "Collision.h"
#include "GameObjectManager.h"
#include "EventManager.h"
#include "Components/ColliderComponent.h"
#include "GameObject.h"
#include "Utillities/Debug_Log.h"

ArksEngine::PhysicsSystem::PhysicsSystem(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}

void ArksEngine::PhysicsSystem::CheckCollision(const GameObjectManager* pEntityManager) const
{
    // Lets loop through our Entities
    for (auto outerIt = pEntityManager->mGameObjects.begin(); outerIt != pEntityManager->mGameObjects.end(); ++outerIt)
    {
        if (!(*outerIt)->HasComponent<ArksEngineComponents::ColliderComponent>() || !(*outerIt)->IsActive())
            continue;

        auto innerIt = outerIt;
        for (++innerIt; innerIt != pEntityManager->mGameObjects.end(); ++innerIt)
        {
            if (!(*innerIt)->HasComponent<ArksEngineComponents::ColliderComponent>() || !(*innerIt)->IsActive())
                continue;

            // What made contact
            const std::unique_ptr<GameObject>& pOwner = *outerIt;
            // what Received Contact
            const std::unique_ptr<GameObject>& pTarget = *innerIt;

            if (Collision::AABB(pOwner->GetComponent<ArksEngineComponents::ColliderComponent>(), pTarget->GetComponent<ArksEngineComponents::ColliderComponent>()))
            {
                // Execute the callback for the owner, passing the target
                pOwner->GetComponent<ArksEngineComponents::ColliderComponent>().ExecuteCallback(pTarget.get());
            }
        }
    }
}
