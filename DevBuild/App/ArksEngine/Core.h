#pragma once
#include <string>

// Core Header
// Jaylin Ferrell


////////////////////////////////////////////////////////
// This is the core of our engine
/////////////////////////////////////////////////////////
namespace ArksEngine
{
	class PhysicsSystem;
	class Debug_Log;
	class Renderer;
	class Window;
	class Input;
	class SceneManager;
	class ResourceManager;
	class LuaSystem;
	class EventManager;
	class LocalizationManager;
	

	class Core
	{
		// Ptr to all of our systems
		ArksEngine::Window* m_pWindow;
		ArksEngine::Renderer* m_pRenderer;
		ArksEngine::Input* m_pInput;
		ArksEngine::Debug_Log* m_pDebug;
		ArksEngine::SceneManager* m_pSceneManager;
		ArksEngine::PhysicsSystem* m_PhysicsSystem;
		ArksEngine::ResourceManager* m_pResourceManager;
		ArksEngine::EventManager* m_pEventManager;
		ArksEngine::LuaSystem* m_pLuaSystem;
		ArksEngine::LocalizationManager* m_pLocalizationManager = nullptr;
		double mDeltaTime;

		// whether to quit at the end of the current frame.
		bool mQuit = false;

	public:
		Core() = default;
		virtual ~Core() = default;

		bool ArksEngine_Initialize(const char* name, const char* assetsFileName, int screenWidth, int screenHeight, const char* localizationFile = nullptr); // This will Initialize the engine and set up SDL..
		void RunEngine();
		void De_initialize() const;

		void SetQuit(bool value) { mQuit = value; }
		bool GetQuit() const { return mQuit; }

		[[nodiscard]] Window* GetWindow() const { return m_pWindow; }
		[[nodiscard]] Renderer* GetRenderer() const { return m_pRenderer; }
		[[nodiscard]] Input* GetInput() const { return m_pInput; }
		[[nodiscard]] Debug_Log* GetDebug_Log() const { return m_pDebug; }
		[[nodiscard]] SceneManager* GetSceneManager() const { return m_pSceneManager; }
		[[nodiscard]] PhysicsSystem* GetPhysicsSystem() const { return m_PhysicsSystem; }
		[[nodiscard]] ResourceManager* GetResourceManager() const { return m_pResourceManager; }
		[[nodiscard]] EventManager* GetEventManager() const { return m_pEventManager; }
		[[nodiscard]] LuaSystem* GetLuaSystem() const { return m_pLuaSystem; }
		[[nodiscard]] double GetDeltaTime() const { return mDeltaTime; }
		[[nodiscard]] LocalizationManager* GetLocalizationManager() const { return m_pLocalizationManager; }

		

		virtual void Update(double deltaTime) {}
		virtual void DisplayOutput() {}

	private:
		[[nodiscard]] int Initialize() const;  // This will Initialize The actual SDL Stuff.
	};
}


