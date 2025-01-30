#include "Core.h"
#include "Input.h"
#include "Renderer.h"
#include "Window.h"
#include "Utillities/Debug_Log.h"
#include "SceneManager.h"
#include "PhysicsSystem.h"
#include "ResourceManager.h"
#include "LuaSystem.h"
#include "EventManager.h"
#include "Event.h"

#include <chrono>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "FontManager.h"
#include "LocalizationManager.h"


bool ArksEngine::Core::ArksEngine_Initialize(const char* name, const char* assetsFileName, int screenWidth, int screenHeight, const char* localizationFile)
{
    m_pDebug = new ArksEngine::Debug_Log;

    Debug_Log::ArksEClearLogs();

    std::cout << "Hello, welcome to the ArksEngine!" << std::endl;
    m_pDebug->Log("Greeting User...");

    m_pDebug->Log("Attempting to initialize engine...");

    if (Initialize() == 0)
    {
        m_pDebug->Log("Initialize successful!");

        m_pWindow = new Window(this);
        m_pWindow->CreateAppWindow(name, screenWidth, screenHeight);

        m_pRenderer = new Renderer(this);
        m_pRenderer->CreateRenderer(m_pWindow);

        m_pResourceManager = new ResourceManager(this, assetsFileName);
        m_pEventManager = new EventManager(this);
        m_pLuaSystem = new LuaSystem(this);
        m_pInput = new Input(this);
        m_pSceneManager = new SceneManager(this);
        m_PhysicsSystem = new ArksEngine::PhysicsSystem(this);

        if (localizationFile)
            m_pLocalizationManager = new LocalizationManager(this, localizationFile);

        return true;
    }

    m_pDebug->Error("Initialize Failed!");
    return false;
}

void ArksEngine::Core::RunEngine()
{
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (!mQuit)
    {
        auto thisFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> lastFrameDuration = thisFrameTime - lastFrameTime;
        const double deltaTime = lastFrameDuration.count();

        mDeltaTime = deltaTime;
        lastFrameTime = thisFrameTime;

        m_pInput->ProcessInput();

        Update(deltaTime);
        DisplayOutput();
    }
}

void ArksEngine::Core::De_initialize() const
{
	delete m_pLocalizationManager;
    delete m_PhysicsSystem;
    delete m_pSceneManager;
    delete m_pInput;
    delete m_pLuaSystem;
    delete m_pEventManager;
    delete m_pResourceManager;
    m_pRenderer->DestroyRenderer();
    delete m_pRenderer;
    m_pWindow->DestroyWindow();
    delete m_pWindow;
    delete m_pDebug;

    SDL_Quit();
}

int ArksEngine::Core::Initialize() const
{
    int errorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO);

    if (errorCode == 0)
    {
        m_pDebug->Log("SDL_Init() succeeded!!");
    }
    else
    {
        m_pDebug->Error("SDL_Init() failed. Error code");
        system("pause");
        return errorCode;
    }

    errorCode = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    if (errorCode == 0)
    {
        m_pDebug->Log("Mix_OpenAudio() succeeded.");
    }
    else
    {
        m_pDebug->Error("Mix_OpenAudio() failed.");
        SDL_Quit();
        return -1;
    }

    int audioFlags = MIX_INIT_MP3;
    errorCode = Mix_Init(audioFlags);

    if (errorCode != audioFlags)
    {
        m_pDebug->Error("Mix_Init() failed.");
        SDL_Quit();
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        m_pDebug->Error("TTF_Init() failed.");
        SDL_Quit();
        return -1;
    }
    
    m_pDebug->Log("TTF_Init() succeeded.");

    return 0;
}
