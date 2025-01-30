#pragma once
#include <string>
#include <utility>

struct lua_State;

namespace ArksEngine
{
	class GameObject;
	class Core;

	class LuaSystem
	{
        
        // Lua state object
        lua_State* m_pLuaState;

        // Pointer to our Core
        Core* m_pOwner;

        // Helper method to push a value onto the Lua stack
        template <typename T>
        static void PushValue(lua_State* state, T value) { lua_push(value); }

        // Overload for const char*, since it needs to be handled differently
        static void PushValue(lua_State* state, const char* value);

        // Helper method to push a single argument onto the Lua stack
        template <typename T>
        void PushArgs(T&& arg) { lua_push(m_pLuaState, std::forward<T>(arg)); }

        // Helper method to push multiple arguments onto the Lua stack
        template <typename T, typename... Args>
        void PushArgs(T&& arg, Args&&... args)
        {
            lua_push(m_pLuaState, std::forward<T>(arg));
            PushArgs(std::forward<Args>(args)...);
        }

    public:
        // Constructor
        LuaSystem(Core* pOwner)
	        :m_pLuaState(nullptr)
			,m_pOwner(pOwner)
        {
	        Init();
        }

        // Destructor
        ~LuaSystem() { Close(); }

        // Initialize Lua state
        void Init();

        // Close Lua state
        void Close() const;

        // Get the Lua state
        [[nodiscard]] lua_State* GetLuaState() const { return m_pLuaState; }

        // Declare your PushCFunction function
        void PushCFunction(const char* name, void* function) const;

        // Get a global variable from Lua
        template <typename tType>
        tType GetGlobalVariable(const char* name);

        // Set a global variable in Lua
        template <typename tType>
        void SetGlobalVariable(const char* name, tType value);

        // Get an element from a Lua array
        template <typename tType>
        tType GetArrayElement(const char* name, int index);

        // Set an element in a Lua array
        template <typename tType>
        void SetArrayElement(const char* name, int index, tType value);

        // Get an element from a Lua table
        template <typename tType>
        tType GetTableElement(const char* name, const char* key);

        // Set an element in a Lua table
        template <typename tType>
        void SetTableElement(const char* name, const char* key, tType value);

        void CallLuaFunction(const std::string& functionName, double deltaTime);
        void CallLuaFunction(const std::string& functionName);

        // Load a Lua script from a file
        bool LoadScript(const char* filename) const;

        void RegisterGameObjectMethods();

        void PushGameObject(lua_State* L, ArksEngine::GameObject* gameObject);

        static int GameObject_GetName(lua_State* L);

        static int GameObject_SetName(lua_State* L);

        template <typename T>
        void SetGlobal(const char* name, T* object);

        void Check();

	private:

        // Convert a Lua value to the specified C++ type
        template <typename tType>
        tType lua_to(lua_State* L, int index);

        // Specializations of lua_to for specific types
        template <>
        int lua_to<int>(lua_State* L, int index);

        template <>
        double lua_to<double>(lua_State* L, int index);

        template <>
        bool lua_to<bool>(lua_State* L, int index);

        template <>
        const char* lua_to<const char*>(lua_State* L, int index);

        // Push a value of the specified C++ type onto the Lua stack
        template <typename tType>
        void lua_push(lua_State* L, tType value);

        // Specializations of lua_push for specific types
        template <>
        void lua_push<int>(lua_State* L, int value);

        template <>
        void lua_push<double>(lua_State* L, double value);

        template <>
        void lua_push<bool>(lua_State* L, bool value);

        template <>
        void lua_push<const char*>(lua_State* L, const char* value);

        template<>
        std::string lua_to<std::string>(lua_State* L, int index);

        template<>
        float lua_to<float>(lua_State* L, int index);
        

       

    
	};
}


