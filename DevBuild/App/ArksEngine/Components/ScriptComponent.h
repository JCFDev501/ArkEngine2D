#pragma once
#include <string>
#include <vector>

#include "Component.h"

namespace ArksEngine
{
	class LuaSystem;
}

namespace ArksEngineComponents
{
	class ScriptComponent : public Component
	{
		std::vector<std::string> mScripts; // A list of script names to be loaded by this component
		ArksEngine::LuaSystem* m_pLuaSystem; // A pointer to the LuaSystem instance used by this component

	public:

		// Construct the ScriptComponent with a pointer to the LuaSystem
		ScriptComponent(ArksEngine::LuaSystem* luaSystem);

		// Add a script to be loaded by this component
		void AddScript(const std::string& scriptName);

		// Remove a script
		void RemoveScript(const std::string& scriptName);

		// Update method for running the scripts
		void Update(double deltaTime) override;
	};
}


