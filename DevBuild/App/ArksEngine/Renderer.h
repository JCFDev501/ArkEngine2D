//Jaylin Ferrell

////////////////////////////////////////////////////////////////////////////
// This is the Renderer class for the engine, this will be were most of the
// Render functions are.
////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cstdint>

struct SDL_Renderer;
struct SDL_Rect;

namespace ArksEngine
{
	class Core;
	class Window;

	class Renderer
	{
		// This is a pointer to the renderer managed by SDL.
		SDL_Renderer* m_pSDLRenderer;

		// This is a pointer to the Core
		ArksEngine::Core* m_pOwner;

	public:
		/**
		 * \brief A constructor
		 * \param pOwner This is a pointer to the Core
		 */
		Renderer(ArksEngine::Core* pOwner);

		/**
		 * \brief A default constructor
		 */
		~Renderer();

		// This functions Clears and the screen then present it
		void RenderPresent() const;

		// Clears screen
		void ClearScreen() const;

		// This is a function that sets the draw color for our shapes 
		void SetRenderDrawColor(int r, int b, int g, int a) const;

		// This sets the color of the rect
		void SetRectColor(const SDL_Rect* pRect) const;

		// TBD....
		void SetCamera(SDL_Rect* pCamera);

		//Shapes.....

		// Rectangle
		void DrawRectangle(int width, int height, int x, int y) const;

		void DrawRectangle(SDL_Rect* pRect) const;

		// Line
		void DrawLine(int x1, int y2, int x2, int y1) const;

		// Circle
		void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius) const;

		// Creates our Renderer
		void CreateRenderer(const ArksEngine::Window* pWindow);

		// Destroys our Renderer
		void DestroyRenderer() const;

		// Gets our Renderer
		[[nodiscard]] SDL_Renderer* GetSDLRenderer() const { return m_pSDLRenderer; }
	private:
		// Math to Draw a Circle 
		static void SDL_DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);
	};
}


