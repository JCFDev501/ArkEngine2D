#include "Renderer.h"
#include <SDL.h>

#include "Core.h"
#include "Window.h"
#include "Utillities/Debug_Log.h"

ArksEngine::Renderer::Renderer(ArksEngine::Core* pOwner)
	:m_pSDLRenderer(nullptr)
	,m_pOwner(pOwner)
{
}

ArksEngine::Renderer::~Renderer()
= default;

/**
 * \brief This function Presents the screen to user
 */
void ArksEngine::Renderer::RenderPresent() const
{
	SDL_RenderPresent(this->m_pSDLRenderer);
}

void ArksEngine::Renderer::ClearScreen() const
{
	SDL_RenderClear(m_pSDLRenderer);
}

/**
 * \brief This function sets the draw color
 * \param r Red
 * \param b Blue
 * \param g Green
 * \param a Opacity
 */
void ArksEngine::Renderer::SetRenderDrawColor(int r, int b, int g, int a) const
{
	SDL_SetRenderDrawColor(this->m_pSDLRenderer, r, g, b, a);
}

void ArksEngine::Renderer::SetRectColor(const SDL_Rect* pRect) const
{
	SDL_RenderFillRect(this->m_pSDLRenderer, pRect);
}

void ArksEngine::Renderer::SetCamera(SDL_Rect* pCamera)
{
	SDL_RenderSetViewport(this->m_pSDLRenderer, pCamera);
}

/**
 * \brief This function Draws a Rectangle
 * \param width Width of the rectangle
 * \param height Height of the rectangle
 * \param x Position of rectangle on X-axis
 * \param y Position of rectangle on Y-axis
 */
void ArksEngine::Renderer::DrawRectangle(int width, int height, int x, int y) const
{
	const SDL_Rect rectangle{ x, y, width, height };

	SDL_RenderDrawRect(this->m_pSDLRenderer, &rectangle);
}

void ArksEngine::Renderer::DrawRectangle(SDL_Rect* pRect) const
{
	SDL_RenderFillRect(this->m_pSDLRenderer, pRect);
}

/**
 * \brief This function draws a line
 * \param x1 The x coordinate of the start point.
 * \param y1 The y coordinate of the start point.
 * \param x2 The x coordinate of the end point.
 * \param y2 The y coordinate of the end point.
 */
void ArksEngine::Renderer::DrawLine(int x1, int y1, int x2, int y2) const
{
	SDL_RenderDrawLine(this->m_pSDLRenderer, x1, y1, x2, y2);
}

/**
 * \brief This function Draws a circle
 * \param centreX x
 * \param centreY y
 * \param radius r
 */
void ArksEngine::Renderer::DrawCircle(int32_t centreX, int32_t centreY, int32_t radius) const
{
	SDL_DrawCircle(m_pSDLRenderer, centreX, centreY, radius);
}

/**
 * \brief This function creates a window
 * \param pWindow This is a pntr to a window
 */
void ArksEngine::Renderer::CreateRenderer(const ArksEngine::Window* pWindow)
{
	m_pOwner->GetDebug_Log()->Log("Attempting to create hardware-accelerated renderer....");

	// Attempts to create a hardware-accelerated renderer for our window.
	this->m_pSDLRenderer = SDL_CreateRenderer(pWindow->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
	if (this->m_pSDLRenderer != nullptr)
	{
		// print success message.
		m_pOwner->GetDebug_Log()->Log("CreateRenderer() succeeded!!");

		// You must set the blend mode if you want to support alpha.
		SDL_SetRenderDrawBlendMode(this->m_pSDLRenderer, SDL_BLENDMODE_BLEND);


	}
	else
	{
		// Print error message and quit.
		m_pOwner->GetDebug_Log()->Log("CreateRenderer() failed");
		SDL_DestroyWindow(pWindow->GetSDLWindow()); // Destroys the window
		SDL_Quit(); // Calls the SDL Quit Function
	}
	
}

/**
 * \brief Destroyes the renderer
 */
void ArksEngine::Renderer::DestroyRenderer() const
{
	SDL_DestroyRenderer(GetSDLRenderer());
}

/**
 * \brief Midpoint Circle Algorithm
 * \param renderer pntr to renderer
 * \param centreX x
 * \param centreY y
 * \param radius r
 */
void ArksEngine::Renderer::SDL_DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

