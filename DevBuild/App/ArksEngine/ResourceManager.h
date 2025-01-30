#pragma once

#include <string>
#include <unordered_map>
#include "Utillities/Zipper.h"

namespace ArksEngine
{
    class Core;

    class ResourceManager
    {
    public:
        ResourceManager(ArksEngine::Core* pOwner, const char* zipFile);
        ~ResourceManager();

        void LoadAssets(const char* zipFileName);

        const std::vector<char>& GetResource(const std::string& resourceName);

        // Other methods will be added in the following steps

    private:
        Core* m_pOwner;
        Zipper* m_pZipper;

        std::unordered_map<std::string, std::vector<char>> m_unzippedAssets;
    };
}

