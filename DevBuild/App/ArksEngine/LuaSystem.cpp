#include "LuaSystem.h"

#include <iostream>

#include "Core.h"

#include <vector>

#include "GameObject.h"
#include "lua.hpp"
#include "ResourceManager.h"
#include "Utillities/Debug_Log.h"

void ArksEngine::LuaSystem::PushValue(lua_State* state, const char* value)
{
	lua_pushstring(state, value);
}

void ArksEngine::LuaSystem::Init()
{
	m_pLuaState = luaL_newstate();
	luaL_openlibs(m_pLuaState);

	RegisterGameObjectMethods();

}

void ArksEngine::LuaSystem::Close() const
{
	lua_close(m_pLuaState);
}

template <>
int ArksEngine::LuaSystem::lua_to<int>(lua_State* L, int index)
{
	return luaL_checkinteger(L, index);
}

template <>
double ArksEngine::LuaSystem::lua_to<double>(lua_State* L, int index)
{
	return luaL_checknumber(L, index);
}

template <>
bool ArksEngine::LuaSystem::lua_to<bool>(lua_State* L, int index)
{
	return lua_toboolean(L, index);
}

template <>
const char* ArksEngine::LuaSystem::lua_to<const char*>(lua_State* L, int index)
{
	return luaL_checkstring(L, index);
}

template <>
void ArksEngine::LuaSystem::lua_push<int>(lua_State* L, int value)
{
	lua_pushinteger(L, value);
}

template <>
void ArksEngine::LuaSystem::lua_push<double>(lua_State* L, double value)
{
	lua_pushnumber(L, value);
}

template <>
void ArksEngine::LuaSystem::lua_push<bool>(lua_State* L, bool value)
{
	lua_pushboolean(L, value);
}

template <>
void ArksEngine::LuaSystem::lua_push<const char*>(lua_State* L, const char* value)
{
	lua_pushstring(L, value);
}

template <>
std::string ArksEngine::LuaSystem::lua_to<std::string>(lua_State* L, int index)
{
	const char* str = lua_tostring(L, index);
	return str ? std::string(str) : std::string();
}

template <>
float ArksEngine::LuaSystem::lua_to<float>(lua_State* L, int index)
{
	return static_cast<float>(lua_tonumber(L, index));
}

bool ArksEngine::LuaSystem::LoadScript(const char* filename) const
{
	// Get the script content from the ResourceManager
	const std::vector<char>& scriptContent = m_pOwner->GetResourceManager()->GetResource(filename);

	// Check if the script content is not empty
	if (!scriptContent.empty()) 
	{
		// Load the script content into the Lua state
		const int loadResult = luaL_loadbuffer(m_pLuaState, scriptContent.data(), scriptContent.size(), filename);

		// Check if the script was loaded successfully
		if (loadResult == LUA_OK) 
		{
			// Execute the script
			const int callResult = lua_pcall(m_pLuaState, 0, LUA_MULTRET, 0);

			// Check if the script executed without errors
			return (callResult == LUA_OK);
		}
	}

	// If the script content is empty or there was an error in loading or executing the script
	return false;
}

//------------------------------------------------------- In the Development Process ----------------------------------------------------------------------------
void ArksEngine::LuaSystem::RegisterGameObjectMethods()
{
	lua_settop(m_pLuaState, 0);

	std::cout << "RegisterGameObjectMethods called" << std::endl;

	luaL_newmetatable(m_pLuaState, "GameObject");
	std::cout << "Top of stack after luaL_newmetatable: " << lua_typename(m_pLuaState, lua_type(m_pLuaState, -1)) << std::endl;

	// Set the __index field of the metatable to be the metatable itself
	// This lets us access the methods when we use the ':' operator in Lua
	lua_pushvalue(m_pLuaState, -1);
	std::cout << "Top of stack after setting __index: " << lua_typename(m_pLuaState, lua_type(m_pLuaState, -1)) << std::endl;
	lua_setfield(m_pLuaState, -2, "__index");

	// Push the GetName function to the table
	lua_pushstring(m_pLuaState, "GetName");
	lua_pushcfunction(m_pLuaState, GameObject_GetName);
	lua_settable(m_pLuaState, -3);

	// Push the SetName function to the table
	lua_pushstring(m_pLuaState, "SetName");
	lua_pushcfunction(m_pLuaState, GameObject_SetName);
	lua_settable(m_pLuaState, -3);

	int isnew = luaL_newmetatable(m_pLuaState, "GameObject");
	std::cout << "Is new metatable? " << isnew << std::endl;

}

void ArksEngine::LuaSystem::PushGameObject(lua_State* L, ArksEngine::GameObject* gameObject)
{
	lua_settop(L, 0);

	std::cout << "PushGameObject called" << std::endl;
	// Push new userdata
	ArksEngine::GameObject** udata = (ArksEngine::GameObject**)lua_newuserdata(L, sizeof(ArksEngine::GameObject*));
	*udata = gameObject;

	// Set the metatable for the userdata
	luaL_getmetatable(L, "GameObject");
	std::cout << "Top of stack after luaL_getmetatable: " << lua_typename(L, lua_type(L, -1)) << std::endl;
	lua_setmetatable(L, -2);

	// Check if the metatable was set
	if (lua_getmetatable(L, -1)) {
		std::cout << "Metatable set correctly." << std::endl;
	}
	else {
		std::cout << "Metatable not set." << std::endl;
	}

	lua_getmetatable(L, -1);
	std::cout << "Top of stack after lua_setmetatable: " << lua_typename(L, lua_type(L, -1)) << std::endl;
	lua_pop(L, 1);

	std::cout << "Metatable: " << lua_typename(L, lua_type(L, -1)) << std::endl;
}

int ArksEngine::LuaSystem::GameObject_GetName(lua_State* L)
{
	// Check and get the GameObject userdata from the stack
	ArksEngine::GameObject* gameObject = *static_cast<ArksEngine::GameObject**>(lua_touserdata(L, 1));
	if (gameObject) 
	{
		// Get the name of the GameObject
		std::string name = gameObject->GetName();

		// Push the name to the Lua stack
		lua_pushstring(L, name.c_str());
		// Return 1 to tell Lua that we've pushed 1 return value to the stack
		return 1;
	}
	else 
	{
		// If the GameObject is null, return an error
		return luaL_error(L, "Failed to get GameObject for GetName");
	}
}

int ArksEngine::LuaSystem::GameObject_SetName(lua_State* L)
{
	// Check and get the GameObject userdata from the stack
	ArksEngine::GameObject* gameObject = static_cast<ArksEngine::GameObject*>(lua_touserdata(L, 1));
	if (gameObject) {
		// Check and get the name from the stack
		const char* name = luaL_checkstring(L, 2);
		// Set the name of the GameObject
		gameObject->SetName(std::string(name));

		// We don't return anything in this function, so return 0
		return 0;
	}
	else {
		// If the GameObject is null, return an error
		return luaL_error(L, "Failed to get GameObject for SetName");
	}
}

//------------------------------------------------------- In the Development Process ----------------------------------------------------------------------------

template <typename tType>
tType ArksEngine::LuaSystem::GetGlobalVariable(const char* name)
{
	lua_getglobal(m_pLuaState, name);
	tType result = lua_to<tType>(m_pLuaState, -1);
	lua_pop(m_pLuaState, 1);
	return result;
}

template <typename tType>
void ArksEngine::LuaSystem::SetGlobalVariable(const char* name, tType value)
{
	lua_push<tType>(m_pLuaState, value);
	lua_setglobal(m_pLuaState, name);
}

template <typename tType>
tType ArksEngine::LuaSystem::GetArrayElement(const char* name, int index)
{
	lua_getglobal(m_pLuaState, name);
	lua_rawgeti(m_pLuaState, -1, index);
	tType result = lua_to<tType>(m_pLuaState, -1);
	lua_pop(m_pLuaState, 2);
	return result;
}

template <typename tType>
void ArksEngine::LuaSystem::SetArrayElement(const char* name, int index, tType value)
{
	lua_getglobal(m_pLuaState, name);
	lua_push<tType>(m_pLuaState, value);
	lua_rawseti(m_pLuaState, -2, index);
	lua_pop(m_pLuaState, 1);
}

template <typename tType>
tType ArksEngine::LuaSystem::GetTableElement(const char* name, const char* key)
{
	lua_getglobal(m_pLuaState, name);
	lua_getfield(m_pLuaState, -1, key);
	tType result = lua_to<tType>(m_pLuaState, -1);
	lua_pop(m_pLuaState, 2);
	return result;
}

template <typename tType>
void ArksEngine::LuaSystem::SetTableElement(const char* name, const char* key, tType value)
{
	lua_getglobal(m_pLuaState, name);
	lua_push<tType>(m_pLuaState, value);
	lua_setfield(m_pLuaState, -2, key);
	lua_pop(m_pLuaState, 1);
}

void ArksEngine::LuaSystem::CallLuaFunction(const std::string& functionName, double deltaTime)
{
	// Push the function name onto the stack
	lua_getglobal(m_pLuaState, functionName.c_str());

	// Push any arguments onto the stack
	lua_pushnumber(m_pLuaState, deltaTime);

	// Call the function
	int result = lua_pcall(m_pLuaState, 1, 0, 0); // 1 argument, 0 return values, no error handler function

	// Check for errors
	if (result != LUA_OK) {
		const char* errMsg = lua_tostring(m_pLuaState, -1);
		std::cout << "Lua error: " << errMsg << std::endl;
		lua_pop(m_pLuaState, 1); // remove the error message from the stack
	}
}

void ArksEngine::LuaSystem::CallLuaFunction(const std::string& functionName)
{
	// Push the function name onto the stack
	lua_getglobal(m_pLuaState, functionName.c_str());

	// Call the function
	int result = lua_pcall(m_pLuaState, 0, 0, 0); // 0 arguments, 0 return values, no error handler function

	// Check for errors
	if (result != LUA_OK) {
		const char* errMsg = lua_tostring(m_pLuaState, -1);
		std::cout << "Lua error: " << errMsg << std::endl;
		lua_pop(m_pLuaState, 1); // remove the error message from the stack
	}
}


void ArksEngine::LuaSystem::PushCFunction(const char* name, void* function) const
{
	// Cast the void pointer back to a lua_CFunction
	const auto lua_function = reinterpret_cast<lua_CFunction>(function);

	// Use the lua_function pointer
	lua_pushcfunction(m_pLuaState, lua_function);
	lua_setglobal(m_pLuaState, name);
}

//------------------------------------------------------- In the Development Process ----------------------------------------------------------------------------
template <typename T>
void ArksEngine::LuaSystem::SetGlobal(const char* name, T* object)
{
	// Push the object onto the stack as a light userdata
    void* userdata = static_cast<void*>(object);
    lua_pushlightuserdata(m_pLuaState, userdata);

    // Set the global variable in Lua
    lua_setglobal(m_pLuaState, name);
}

void ArksEngine::LuaSystem::Check()
{
	//
}

template void ArksEngine::LuaSystem::SetGlobal<ArksEngine::GameObject>(const char* name, ArksEngine::GameObject* object);

template int ArksEngine::LuaSystem::GetArrayElement<int>(const char* name, int index);
template std::string ArksEngine::LuaSystem::GetArrayElement<std::string>(const char* name, int index);
template float ArksEngine::LuaSystem::GetArrayElement<float>(const char* name, int index);

template int ArksEngine::LuaSystem::GetGlobalVariable<int>(const char* name);
template std::string ArksEngine::LuaSystem::GetGlobalVariable<std::string>(const char* name);
template float ArksEngine::LuaSystem::GetGlobalVariable<float>(const char* name);

template int ArksEngine::LuaSystem::GetTableElement<int>(const char* tableName, const char* key);
template std::string ArksEngine::LuaSystem::GetTableElement<std::string>(const char* tableName, const char* key);
template float ArksEngine::LuaSystem::GetTableElement<float>(const char* tableName, const char* key);

template void ArksEngine::LuaSystem::SetArrayElement<int>(const char* name, int index, int value);

template void ArksEngine::LuaSystem::SetGlobalVariable<int>(const char* name, int value);

template void ArksEngine::LuaSystem::SetTableElement<int>(const char* tableName, const char* key, int value);




//------------------------------------------------------- In the Development Process ----------------------------------------------------------------------------