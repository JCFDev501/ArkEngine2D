#pragma once
/**
 * \brief This is were All of our different type of collisions will go
 */
namespace ArksEngineComponents
{
	class ColliderComponent;
}

struct SDL_Rect;

namespace ArksEngine
{
	class Collision
	{
	public:
		/**
		 * \brief An Axis Aligned Bounding Box (AABB)
		 * \param colliderA Object 1
		 * \param colliderB object 2
		 * \return true or false depending on if a collision occurred
		 */
		static bool AABB(const ArksEngineComponents::ColliderComponent& colliderA, const ArksEngineComponents::ColliderComponent
		                 & colliderB);
	};
}


