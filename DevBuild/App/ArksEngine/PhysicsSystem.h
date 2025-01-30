#pragma once
#include "Core.h"

namespace ArksEngine
{
	class GameObjectManager;

	class PhysicsSystem
	{
		// This is a Ptr to the Core
		ArksEngine::Core* m_pOwner;

	public:
		/**
		 * \brief A constructor
		 * \param pOwner This is a Ptr to the Core
		 */
		PhysicsSystem(ArksEngine::Core* pOwner);
		/**
		 * \brief A default DE-Constructor
		 */
		~PhysicsSystem() = default;

		/**
		 * \brief This Checks for collisions between Entities in a Scene  
		 * \param pEntityManager A pointer to a scenes Entity Manager
		 */
		void CheckCollision(const GameObjectManager* pEntityManager) const;
	};
}
