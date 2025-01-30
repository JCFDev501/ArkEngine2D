#pragma once
#include <string>
#include <vector>

#include "Texture.h"

namespace ArksEngine
{
	class GameObject;
	class GameObjectManager;
	class Core;

    class Level
    {
	    struct CollisionInfo
	    {
            GameObject* p_entity;
            bool hasWidth = false;
            bool hasHeight = false;
	    };


        ArksEngine::Core* m_pOwner;
        ArksEngine::Texture* m_pLevelImage{};
        ArksEngine::Texture* m_pCollisionMap{};
        GameObjectManager* m_pEntityManager;
        std::vector<std::vector<bool>> mCollisionData;

        float mWidth{};
        float mHeight{};

    public:
        Level(ArksEngine::Core* pOwner, GameObjectManager* pManager);

        void LoadLevel(Texture* level, Texture* levelCollisionMap, float widthOfLevel, float heightOfLevel);

        ~Level()
        {
            //delete m_pLevelImage;
            //delete m_pCollisionMap;
        }

        void Render(float positionX, float positionY);
        void Render() const;
        void GenerateCollisionDataFromCollisionMap();
        void CreateColliders();
        void ProcessColliders(std::vector<CollisionInfo>& colliders, int x, int y);
        void CreateNewCollider(std::vector<CollisionInfo>& colliders, int x, int y);

    };
}


