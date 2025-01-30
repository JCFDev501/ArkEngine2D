#include "Collision.h"

#include <SDL_rect.h>

#include "Components/ColliderComponent.h"


bool ArksEngine::Collision::AABB(const ArksEngineComponents::ColliderComponent& colliderA, const ArksEngineComponents::ColliderComponent
                                 & colliderB)
{
	const SDL_Rect boxA = *colliderA.GetCollider();
	const SDL_Rect boxB = *colliderB.GetCollider();

	if(boxA.x + boxA.w >= boxB.x && boxB.x + boxB.w >= boxA.x 
		&& boxA.y + boxA.h >= boxB.y && boxB.y + boxB.h >= boxA.y)
	{
		return true; // There has been a collision
	}

	return false; // No collision
}
