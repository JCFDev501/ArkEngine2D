#pragma once
#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Components/Component.h"
 
using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename tType>
inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
using ComponentArray = std::array<ArksEngineComponents::Component*, maxComponents>;

namespace ArksEngine
{
	// The GameObject class, representing an individual game object that can have multiple components.
	class GameObject
	{
		bool mIsActive = true;
		bool mIsDestroyed = false;
		std::string mName = "Unknown";
		std::string mTag = "Unknown";

		std::vector<std::unique_ptr<ArksEngineComponents::Component>> mComponents;
		ComponentArray mComponentArray = {};

	public:
		GameObject()
		{
			mComponents.reserve(maxComponents); // Reserving space for performance.
		}

		// Updates all components attached to this entity.
		void Update(double deltaTime) const
		{
			for (auto& component : mComponents)
				component->Update(deltaTime);
		}

		// Renders all components attached to this entity at a offset.
		void Render(float xOffset) const
		{
			for (auto& component : mComponents)
				component->Render(xOffset);
		}

		// Checks if entity is Destroyed
		bool GetIsDestroyed() const { return mIsDestroyed; }
		void Destroy() { mIsDestroyed = true; }

		// Checks if our Game obj is Active
		bool IsActive() const { return mIsActive; }
		void SetActive(bool val) { mIsActive = val; }

		// Getters/Setters
		[[nodiscard]] const std::string& GetName() const { return mName; }
		[[nodiscard]] const std::string& GetTag() const { return mTag; }
		void SetName(std::string name) { mName = std::move(name); }
		void SetTag(std::string tag) { mTag = std::move(tag); }

		// Check to see if GameObject has this component.
		template<typename tType>
		[[nodiscard]] bool HasComponent() const
		{
			return mComponentArray[GetComponentTypeID<tType>()] != nullptr;
		}

		// Adds a new component of type tType to the entity and initializes it.
		template<typename tType, typename... tArgs>
		tType& AddComponent(tArgs&&... mArgs)
		{
			auto component = std::make_unique<tType>(std::forward<tArgs>(mArgs)...);
			component->mGameObj = this;

			mComponentArray[GetComponentTypeID<tType>()] = component.get();
			mComponents.emplace_back(std::move(component));

			mComponentArray[GetComponentTypeID<tType>()]->Init();
			return *static_cast<tType*>(mComponentArray[GetComponentTypeID<tType>()]);
		}

		// Retrieves the component of type tType from the entity, if it exists.
		template<typename tType>
		tType& GetComponent() const
		{
			auto ptr = mComponentArray[GetComponentTypeID<tType>()];
			if (!ptr)
			{
				std::cout << "Component not found!";
			}
			return *static_cast<tType*>(ptr);
		}
	};

}


