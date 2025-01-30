#include "ResourceManager.h"
#include "Core.h"
#include "Utillities/Debug_Log.h"

// ResourceManager constructor
ArksEngine::ResourceManager::ResourceManager(Core* pOwner, const char* zipFileName)
    : m_pOwner(pOwner)
{
    LoadAssets(zipFileName);
}

ArksEngine::ResourceManager::~ResourceManager()
{
    delete m_pZipper;
}

// LoadAssets function
void ArksEngine::ResourceManager::LoadAssets(const char* zipFileName)
{
    // Create a new instance of the Zipper class
    m_pZipper = new Zipper(m_pOwner);

    // Load the assets zip file
    if (!m_pZipper->LoadZipFile(zipFileName))
    {
        // Log an error if the zip file could not be loaded
        m_pOwner->GetDebug_Log()->Error("Failed to load assets.zip");
    }
    else
    {
        // Iterate through the unzipped assets and insert them into the ResourceManager's m_unzippedAssets map
        const auto& zipperAssets = m_pZipper->Get_UnzippedAssets();
        for (const auto& asset : zipperAssets)
        {
            m_unzippedAssets[asset.first] = asset.second;
        }
    }
}

const std::vector<char>& ArksEngine::ResourceManager::GetResource(const std::string& resourceName)
{
    auto it = m_unzippedAssets.find(resourceName);

    if (it != m_unzippedAssets.end())
    {
        return it->second;
    }
    
    
	// Log an error if the resource was not found
	m_pOwner->GetDebug_Log()->Error("Resource not found: " + resourceName);

	// Return an empty vector if the resource was not found
	static const std::vector<char> emptyResource;
	return emptyResource;
    
}
