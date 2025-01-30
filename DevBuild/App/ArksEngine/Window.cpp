#include "Window.h"
#include <SDL.h>

#include "Core.h"
#include "Utillities/Debug_Log.h"

ArksEngine::Window::Window(ArksEngine::Core* pOwner)
	:m_pSDLWindow(nullptr)
	,m_pOwner(pOwner)
	,mWidth(0)
	,mHeight(0)
{
}

ArksEngine::Window::~Window()
= default;

void ArksEngine::Window::CreateAppWindow(const char* name, int width, int height)
{
	mWidth = width; 
	mHeight = height;

	// Attempts to create a maximized window that can be restored to a 960x608, centered window.
	m_pSDLWindow = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		mWidth, mHeight,
		0);
	if (m_pSDLWindow != nullptr)
	{
		// Log a success message.
		m_pOwner->GetDebug_Log()->Log("(SDL_CreateWindow() succeeded!!");
		//system("pause");
	}
	else
	{
		// Print error message and quit.
		m_pOwner->GetDebug_Log()->Error("(SDL_CreateWindow() failed.");
		system("pause");
	}
}

void ArksEngine::Window::DestroyWindow() const
{
	SDL_DestroyWindow(GetSDLWindow());
}
