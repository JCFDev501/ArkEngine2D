#include "ScriptComponent.h"

#include <iostream>
#include <ostream>

#include "../LuaSystem.h"

ArksEngineComponents::ScriptComponent::ScriptComponent(ArksEngine::LuaSystem* luaSystem)
	:m_pLuaSystem(luaSystem)
{
}

void ArksEngineComponents::ScriptComponent::AddScript(const std::string& scriptName)
{
    // Load the script before trying to call any functions
    bool isLoaded = m_pLuaSystem->LoadScript(scriptName.c_str());

    // Only proceed if the script was loaded successfully
    if (isLoaded)
    {
        // Store the script name
        mScripts.push_back(scriptName);

        // Call the "Start" function
        m_pLuaSystem->CallLuaFunction("Start");
    }
    else
    {
        std::cout << "Failed to load script: " << scriptName << std::endl;
    }
}


void ArksEngineComponents::ScriptComponent::RemoveScript(const std::string& scriptName)
{
    // Finds the first instance of scriptName
    auto pos = std::find(mScripts.begin(), mScripts.end(), scriptName);

    // If the script name was found, remove it
    if (pos != mScripts.end()) 
        mScripts.erase(pos);
    
}

void ArksEngineComponents::ScriptComponent::Update(double deltaTime)
{
    for (const auto& script : mScripts)
    {
        m_pLuaSystem->CallLuaFunction("Update", deltaTime);
    }
    
}


