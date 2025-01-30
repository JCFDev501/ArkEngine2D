#include "AiControllerComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"

ArksEngineComponents::AiControllerComponent::AiControllerComponent(ArksEngine::Core* pOwner, float speed)
	:m_pOwner(pOwner)
	, m_speed(speed)
{
}

void ArksEngineComponents::AiControllerComponent::Init()
{
	// Initialize if needed, e.g., get a reference to the TransformComponent
	m_pTransformRef = &mGameObj->GetComponent<TransformComponent>();
}

void ArksEngineComponents::AiControllerComponent::Update(double deltaTime)
{
    if (m_pTarget != nullptr)
    {

        // Get positions of AI and target
        auto aiPosition = m_pTransformRef->GetPosition();

        auto targetPosition = m_pTarget->GetComponent<TransformComponent>().GetPosition();

        // Calculate direction vector from AI to target
        float deltaX = targetPosition.m_x - aiPosition.m_x;
        float deltaY = targetPosition.m_y - aiPosition.m_y;

        // Calculate distance to the target
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // Check if the target is within a certain range before moving
        if (distance > 0.0f) // Prevent division by zero
        {
            // Normalize the direction vector
            float directionX = deltaX / distance;
            float directionY = deltaY / distance;

            // Move the AI towards the target
            aiPosition.m_x += directionX * m_speed * deltaTime; // Move in the x direction
            aiPosition.m_y += directionY * m_speed * deltaTime; // Move in the y direction

            // Update the AI's position in the TransformComponent
            m_pTransformRef->SetPosition(aiPosition.m_x, aiPosition.m_y);
        }
    }
    else
    {
        std::cout << "No target set!" << std::endl; // Debug output for no target
    }
}


