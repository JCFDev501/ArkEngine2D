#include "GameObjectManager.h"
#include "GameObject.h"
#include "Components/TransformComponent.h"

void ArksEngine::GameObjectManager::Update(double deltaTime) const
{
	for (const auto& game_object : mGameObjects)
	{
		if (game_object->IsActive())
			game_object->Update(deltaTime);
	}
		
}

void ArksEngine::GameObjectManager::Render(float xOffset) const
{
	for (const auto& game_object : mGameObjects)
	{
		if (game_object->IsActive())
			game_object->Render(xOffset);
	}
		
}

void ArksEngine::GameObjectManager::Render() const
{
	for (const auto& game_object : mGameObjects)
	{
		if (game_object->IsActive())
			game_object->Render(0);
	}
		
}

void ArksEngine::GameObjectManager::Refresh()
{
	mGameObjects.erase(std::remove_if(std::begin(mGameObjects), std::end(mGameObjects),
		[](const std::unique_ptr<GameObject>& mEntity)
		{
			return mEntity->GetIsDestroyed();
		}),
		std::end(mGameObjects));
}

void ArksEngine::GameObjectManager::SetGameObjActiveBasedOffTag(const std::string& tag, bool val) const
{
	for (const auto& game_object : mGameObjects)
	{
		if (game_object->GetTag() == tag)
		{
			game_object->SetActive(val);
		}
	}
}

ArksEngine::GameObject& ArksEngine::GameObjectManager::AddGameObject()
{
	const auto game_object = new GameObject();

	game_object->AddComponent<ArksEngineComponents::TransformComponent>(); // All Game objects should auto have a transform

	std::unique_ptr<GameObject> uPtr{ game_object };

	mGameObjects.emplace_back(std::move(uPtr));
	

	return *game_object;
}

ArksEngine::GameObject* ArksEngine::GameObjectManager::GetGameObject(const std::string& name) const
{
	for (const auto& game_object : mGameObjects)
	{
		if (game_object->GetName() == name)
		{
			return game_object.get();
		}
	}

	// Return nullptr if no entity with the specified tag is found.
	return nullptr;
}
