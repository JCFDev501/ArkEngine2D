#include "FontManager.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "Core.h"
#include "Renderer.h"
#include "Utillities/Debug_Log.h"


// Define static color constants
const SDL_Color ArksEngine::FontManager::WHITE = { 255, 255, 255, 255 };
const SDL_Color ArksEngine::FontManager::BLACK = { 0, 0, 0, 255 };
const SDL_Color ArksEngine::FontManager::RED = { 255, 0, 0, 255 };
const SDL_Color ArksEngine::FontManager::GREEN = { 0, 255, 0, 255 };
const SDL_Color ArksEngine::FontManager::BLUE = { 0, 0, 255, 255 };
const SDL_Color ArksEngine::FontManager::YELLOW = { 255, 255, 0, 255 };

ArksEngine::FontManager::FontManager(ArksEngine::Core* pOwner)
	:m_pOwner(pOwner)
{
}

bool ArksEngine::FontManager::LoadFont(const char* path, int fontSize)
{
	m_pFont = TTF_OpenFont(path, fontSize);
	if (m_pFont == nullptr)
		return false;

	return true;
}

SDL_Texture* ArksEngine::FontManager::RenderText(const std::string& text, const SDL_Color& color)
{
	if (m_pFont == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Font is not loaded!");
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(m_pFont, text.c_str(), color);
	//if (surface == nullptr) 
	//{
	//	m_pOwner->GetDebug_Log()->Error("Error creating surface!");
	//	return nullptr;
	//}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pOwner->GetRenderer()->GetSDLRenderer(), surface);
	SDL_FreeSurface(surface);

	//if (texture == nullptr) 
	//{
	//	m_pOwner->GetDebug_Log()->Error("Error creating texture!");
	//	return nullptr;
	//}

	return texture;
}

void ArksEngine::FontManager::RenderTextToScreen(const std::string& text, const SDL_Color& color,
	int x, int y, int maxWidth, int maxHeight)
{
	// Render the text to a texture
	SDL_Texture* texture = RenderText(text, color);
	//if (!texture)
	//{
	//	m_pOwner->GetDebug_Log()->Error("Unable to render text to texture!");
	//	return;
	//}

	// Get texture dimensions
	int textWidth = 0;
	int textHeight = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

	// Check if the text exceeds the provided bounds and scale if necessary
	float scale = 1.0f;
	if (textWidth > maxWidth || textHeight > maxHeight)
	{
		// Calculate the scaling factor based on the max width and height
		float scaleX = static_cast<float>(maxWidth) / static_cast<float>(textWidth);
		float scaleY = static_cast<float>(maxHeight) / static_cast<float>(textHeight);

		// Use the smaller scale factor to preserve the aspect ratio
		scale = (scaleX < scaleY) ? scaleX : scaleY;

		// Apply the scale to the text dimensions
		textWidth = static_cast<int>(textWidth * scale);
		textHeight = static_cast<int>(textHeight * scale);
	}

	// Define destination rectangle for rendering, using the scaled width and height
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = textWidth;
	destRect.h = textHeight;

	// Copy the texture to the renderer, rendering it within the calculated bounds
	SDL_RenderCopy(m_pOwner->GetRenderer()->GetSDLRenderer(), texture, nullptr, &destRect);

	// Clean up the texture
	SDL_DestroyTexture(texture);
}


void ArksEngine::FontManager::CloseFont()
{
	if (m_pFont != nullptr) 
	{
		TTF_CloseFont(m_pFont);
		m_pFont = nullptr;
	}
}

int ArksEngine::FontManager::GetTextWidth(const std::string& text, int fontSize) const
{
	if (m_pFont == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Font is not loaded!");
		return 0;
	}

	int width = 0;
	int height = 0;
	if (TTF_SizeText(m_pFont, text.c_str(), &width, &height) != 0)
	{
		m_pOwner->GetDebug_Log()->Error("Error calculating text width!");
		return 0;
	}

	return width;
}

int ArksEngine::FontManager::GetTextHeight(const std::string& text, int fontSize) const
{
	if (m_pFont == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Font is not loaded!");
		return 0;
	}

	int width = 0;
	int height = 0;
	if (TTF_SizeText(m_pFont, text.c_str(), &width, &height) != 0)
	{
		m_pOwner->GetDebug_Log()->Error("Error calculating text height!");
		return 0;
	}

	return height;
}
