#include "Level.h"
#include <SDL_stdinc.h>
#include "Components/TransformComponent.h"
#include "Components/ColliderComponent.h"
#include "Core.h"
#include "GameObject.h"
#include "GameObjectManager.h"


namespace ArksEngineComponents
{
    class ColliderComponent;
}

// Constructor for the Level class
ArksEngine::Level::Level(ArksEngine::Core* pOwner, GameObjectManager* pManager)
    :m_pOwner(pOwner)
    , m_pEntityManager(pManager)
{
}

// Load level data and create colliders from the collision map
void ArksEngine::Level::LoadLevel(Texture* level, Texture* levelCollisionMap, float widthOfLevel, float heightOfLevel)
{
    m_pLevelImage = level;
    m_pCollisionMap = levelCollisionMap;
    mWidth = widthOfLevel;
    mHeight = heightOfLevel;

    GenerateCollisionDataFromCollisionMap();

    CreateColliders();
}

// Render the level at the specified position
void ArksEngine::Level::Render(float positionX, float positionY)
{
    Vector2F position = { positionX, positionY };
    Vector2F dimensions = { mWidth, mHeight };

    m_pLevelImage->RenderTexture(position, dimensions);

    // Render the collision map directly on the screen for debugging purposes
	//m_pCollisionMap->RenderTexture(position, dimensions);
}

void ArksEngine::Level::Render() const
{
    if (m_pLevelImage)
		m_pLevelImage->RenderTexture(Vector2F{ 0, 0 }, Vector2F{ mWidth, mHeight });
	//m_pCollisionMap->RenderTexture(Vector2F{ 0, 0 }, Vector2F{ mWidth, mHeight });
}

// Generate collision data from the collision map
void ArksEngine::Level::GenerateCollisionDataFromCollisionMap()
{
    int width, height;
    m_pCollisionMap->GetDimensions(width, height);

    // Resize the mCollisionData matrix to match the level size
    mCollisionData.resize(height, std::vector<bool>(width));

    m_pCollisionMap->AccessPixels([this](int x, int y, Uint8 r, Uint8 g, Uint8 b) {
        // Red pixels (255, 0, 0) represent colliders.
        bool isCollider = (r == 255 && g == 0 && b == 0);
        mCollisionData[y][x] = isCollider;
        });

}

// Create colliders based on the collision data
void ArksEngine::Level::CreateColliders()
{
    std::vector<CollisionInfo> colliders;

    // Iterate through the collision data
    for (size_t y = 0; y < mCollisionData.size(); ++y)
    {
        for (size_t x = 0; x < mCollisionData[y].size(); ++x)
        {
            if (x == 328)
            {
                int j = 2;
            }
            // Handle the case where the cell is not a collider and an adjacent cell is a collider
            if (!mCollisionData[y][x] && ((x != 0 && mCollisionData[y][x - 1]) || (y != 0 && mCollisionData[y - 1][x])))
            {
                ProcessColliders(colliders, x, y);
            }
            // Handle the case where the cell is at the edge of the collision data and is a collider
            else if ((x == mCollisionData[y].size() - 1 && mCollisionData[y][x]) || (y == mCollisionData.size() - 1 && mCollisionData[y][x]))
            {
                ProcessColliders(colliders, x, y);
            }
            // Handle the case where the cell is a collider
            else if (mCollisionData[y][x])
            {
                CreateNewCollider(colliders, x, y);
            }
        }
    }
}

// Function to process colliders for a given x and y position
void ArksEngine::Level::ProcessColliders(std::vector<CollisionInfo>& colliders, int x, int y)
{
    for (size_t i = 0; i < colliders.size(); ++i)
    {
        auto& transform = colliders[i].p_entity->GetComponent<ArksEngineComponents::TransformComponent>();
        auto& collider = colliders[i].p_entity->GetComponent<ArksEngineComponents::ColliderComponent>();

        if (transform.GetPosition().m_y == y && !colliders[i].hasWidth)
        {
            float scale = transform.GetScale().m_y;
            float positionX = transform.GetPosition().m_x;
            transform.SetScale(x - positionX - 1, scale);
            colliders[i].hasWidth = true;
        }
        else if (transform.GetPosition().m_x == x && !colliders[i].hasHeight)
        {
            float scale = transform.GetScale().m_x;
            float positionY = transform.GetPosition().m_y;
            transform.SetScale(scale, y - positionY - 1);
            colliders[i].hasHeight = true;
        }
        else if (colliders[i].hasHeight && colliders[i].hasWidth)
        {
            collider.SetWidth(transform.GetScale().m_x);
            collider.SetHeight(transform.GetScale().m_y);

            colliders.erase(colliders.begin() + i);
        }
    }
}

// Function to create a new collider for a given x and y position
void ArksEngine::Level::CreateNewCollider(std::vector<CollisionInfo>& colliders, int x, int y)
{
    if ((x == 0 || !mCollisionData[y][x - 1]) && (y == 0 || !mCollisionData[y - 1][x]))
    {
        CollisionInfo newInfo;
        GameObject& newEntity(m_pEntityManager->AddGameObject());

        newEntity.SetName("Collider");
        newEntity.SetTag("Wall");

        // Add components to the new entity
        newEntity.AddComponent<ArksEngineComponents::TransformComponent>();
        newEntity.GetComponent<ArksEngineComponents::TransformComponent>().SetPosition(x, y);
        newEntity.AddComponent<ArksEngineComponents::ColliderComponent>(m_pOwner->GetRenderer());

        // Set the pointer to the new entity in the CollisionInfo struct
        newInfo.p_entity = &newEntity;

        // Add the new CollisionInfo object to the colliders container (assuming colliders is a vector or similar container)
        colliders.emplace_back(newInfo);
    }
}
