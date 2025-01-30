#include "Texture.h"
#include <SDL_image.h>
#include <SDL_render.h>
#include <vector>
#include "Core.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Window.h"
#include "Utillities/Math.h"


ArksEngine::Texture::Texture(ArksEngine::Core* pOwner, const char* fileName)
	:m_pOwner(pOwner)
	,m_pFileName(fileName)
	,m_pTexture(nullptr)
{
	LoadNewTexture(pOwner->GetRenderer()->GetSDLRenderer());
}

ArksEngine::Texture::Texture(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
	,m_pTexture(nullptr)
{
}

void ArksEngine::Texture::AccessPixels(const std::function<void(int x, int y, uint8_t r, uint8_t g, uint8_t b)>&
	pixelCallback) const
{
	int width, height;

	// Query the width and height of the texture using SDL_QueryTexture().
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &width, &height);

	// Get the screen width and height to 960 and 480 respectively.
	int screenWidth = m_pOwner->GetWindow()->GetScreenWidth();
	int screenHeight = m_pOwner->GetWindow()->GetScreenHeight();

	/// <summary>
	/// Loop through the texture in chunks of screenWidth and screenHeight.
	/// This is done to avoid reading the entire texture at once, which could be slow and cause memory issues.
	/// </summary>
	/// <param name="pixelCallback">
	/// The callback function pixelCallback is a function that is passed as a parameter to the AccessPixels() method.
	/// It takes five parameters: int x, int y, uint8_t r, uint8_t g, and uint8_t b.
	/// </param>
	for (int offsetY = 0; offsetY < height; offsetY += screenHeight)
	{
		for (int offsetX = 0; offsetX < width; offsetX += screenWidth)
		{
			// Determine the width and height of the current chunk based on the remaining pixels in the texture.
			const int chunkWidth = ArksEngine::Math<int>::Min(width - offsetX, screenWidth);
			const int chunkHeight = ArksEngine::Math<int>::Min(height - offsetY, screenHeight);
			
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Create a temporary surface and texture using SDL_CreateRGBSurfaceWithFormat() and SDL_CreateTextureFromSurface() respectively.
			/// These will be used to read the pixel values of the current chunk.
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			SDL_Surface* tempSurface = SDL_CreateRGBSurfaceWithFormat(0, chunkWidth, chunkHeight, 32, SDL_PIXELFORMAT_ABGR8888);
			SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(m_pOwner->GetRenderer()->GetSDLRenderer(), tempSurface);

			// Set the temporary texture as the render target
			SDL_SetRenderTarget(m_pOwner->GetRenderer()->GetSDLRenderer(), tempTexture);

			// Copy the current chunk of the texture to the temporary texture
			SDL_Rect srcRect = { offsetX, offsetY, chunkWidth, chunkHeight };
			SDL_Rect destRect = { 0, 0, chunkWidth, chunkHeight };
			SDL_RenderCopy(m_pOwner->GetRenderer()->GetSDLRenderer(), m_pTexture, &srcRect, &destRect);

			// Read the pixel values of the temporary surface
			SDL_RenderReadPixels(m_pOwner->GetRenderer()->GetSDLRenderer(), nullptr, tempSurface->format->format, tempSurface->pixels, tempSurface->pitch);

			// Reset the render target
			SDL_SetRenderTarget(m_pOwner->GetRenderer()->GetSDLRenderer(), nullptr);

			/// <summary>
			/// Loop through each pixel in the chunk and
			/// call the pixelCallback function with the
			/// x, y, red, green, and blue values of each pixel.
			/// </summary>
			/// <param name="pixelCallback"></param>
			for (int y = 0; y < chunkHeight; ++y)
			{
				for (int x = 0; x < chunkWidth; ++x)
				{
					const uint32_t pixel = static_cast<uint32_t*>(tempSurface->pixels)[y * chunkWidth + x];
					Uint8 r, g, b;
					SDL_GetRGB(pixel, tempSurface->format, &r, &g, &b);

					if (x == 100)
					{
						int h = 2;
					}

					pixelCallback(x + offsetX, y + offsetY, r, g, b);
				}
			}
			//Free the temporary surface and texture
			SDL_FreeSurface(tempSurface);
			SDL_DestroyTexture(tempTexture);
		}
	}
}

void ArksEngine::Texture::GetDimensions(int& width, int& height) const
{
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &width, &height);
}

void ArksEngine::Texture::LoadNewTexture(SDL_Renderer* pRenderer)
{

	// Define the path to the assets folder
	std::string assetPath = "Assets/";  // Adjust this to your actual assets folder location
	std::string fullPath = assetPath + m_pFileName;

	// Load image directly from the file in the assets folder
	SDL_Surface* pImageSurface = IMG_Load(fullPath.c_str());

	if (pImageSurface == nullptr)
	{
		// Handle error if the file could not be loaded
		return;
	}

	// Convert surface to texture
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
	if (pTexture == nullptr)
	{
		SDL_FreeSurface(pImageSurface);
		return;
	}

	// Store the created texture
	m_pTexture = pTexture;

	// Free the surface after creating the texture
	SDL_FreeSurface(pImageSurface);


	//// Get resource data from ResourceManager
	//const std::vector<char>& resourceData =  m_pOwner->GetResourceManager()->GetResource(m_pFileName);
	//
	//// Load image from memory
	//SDL_RWops* rwops = SDL_RWFromConstMem(resourceData.data(), resourceData.size());
	//SDL_Surface* pImageSurface = IMG_Load_RW(rwops, 1);
	//
	////SDL_Surface* pImageSurface = IMG_Load(m_pFileName);
	//if (pImageSurface == nullptr)
	//{
	//	return;
	//}
	//	
	//
	//// Convert surface to texture
	//SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pImageSurface);
	//if (pTexture == nullptr)
	//{
	//	return;
	//}
	//
	//m_pTexture = pTexture;
	//
	//// Free surface
	//SDL_FreeSurface(pImageSurface);
}

void ArksEngine::Texture::RenderTexture(Vector2F source, Vector2F destination, Vector2F dimensions) const
{
	SDL_Rect scr, dest;

	scr.x = static_cast<int>(source.m_x);
	scr.y = static_cast<int>(source.m_y);
	scr.w = static_cast<int>(dimensions.m_x);
	scr.h = static_cast<int>(dimensions.m_y);

	dest.x = static_cast<int>(destination.m_x);
	dest.y = static_cast<int>(destination.m_y);
	dest.w = scr.w;
	dest.h = scr.h;


	if (m_pTexture == nullptr)
	{
		return;
	}

	SDL_RenderCopy(m_pOwner->GetRenderer()->GetSDLRenderer(), m_pTexture, &scr, &dest);
}

void ArksEngine::Texture::RenderTexture(Vector2F destination, Vector2F dimensions) const
{
	SDL_Rect dest;

	dest.x = static_cast<int>(destination.m_x);
	dest.y = static_cast<int>(destination.m_y);
	dest.w = static_cast<int>(dimensions.m_x);
	dest.h = static_cast<int>(dimensions.m_y);

	if (m_pTexture == nullptr)
	{
		// error
		return;
	}

	SDL_RenderCopy(m_pOwner->GetRenderer()->GetSDLRenderer(), m_pTexture, nullptr, &dest);
}

void ArksEngine::Texture::RenderTexture(float x, float y, SDL_Rect* clip, double angle, SDL_Point* center) const
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	//Set rendering space and render to screen
	SDL_Rect renderQuad = { static_cast<int>(x), static_cast<int>(y), 0, 0 };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(m_pOwner->GetRenderer()->GetSDLRenderer(), m_pTexture, clip, &renderQuad, angle, center, flip);
}
