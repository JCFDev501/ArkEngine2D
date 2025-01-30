#pragma once
#include "Window.h"

struct SDL_Window;

namespace ArksEngine
{
	class Core;

	class Window
	{
		// Pointer to the application window managed by SDL.
		SDL_Window* m_pSDLWindow;

		ArksEngine::Core* m_pOwner;

		int mWidth; // width of our window
		int mHeight; // height of our vindow

	public:

		Window(ArksEngine::Core* pOwner);
		~Window();

		/**
		 * \brief This creates a window for our game / App
		 * \param name The name of our window
		 * \param width The width of our window
		 * \param height The height of our window
		 */
		void CreateAppWindow(const char* name, int width, int height);
		/**
		 * \brief Destroys our window
		 */
		void DestroyWindow() const;
		/**
		 * \brief Gets our window
		 * \return a ptr to Sdl_window
		 */
		[[nodiscard]] SDL_Window* GetSDLWindow() const { return m_pSDLWindow; }

		[[nodiscard]] int GetScreenWidth() const { return mWidth; } // Gets our screen width
		[[nodiscard]] int GetScreenHeight() const { return mHeight; } // Gets our screen height
	};
}


