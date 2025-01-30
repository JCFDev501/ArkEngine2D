#pragma once
#include <string>

typedef struct _TTF_Font TTF_Font;

struct SDL_Color;
struct SDL_Renderer;
struct SDL_Texture;



namespace ArksEngine
{

	class Core;

	class FontManager
	{

		TTF_Font* m_pFont = nullptr;

		ArksEngine::Core* m_pOwner = nullptr;

	public:
		FontManager(ArksEngine::Core* pOwner);
		~FontManager() = default;

		// Load a font from a file using char* instead of std::string
		bool LoadFont(const char* path, int fontSize);

		// Render text as an SDL_Texture using char* instead of std::string
		SDL_Texture* RenderText(const std::string& text, const SDL_Color& color );

		// New method: Render text directly to the screen
		void RenderTextToScreen(const std::string& text, const SDL_Color& color, int x, int y, int width, int height);


		// Close and free the font resource
		void CloseFont();


		int GetTextWidth(const std::string& text, int fontSize) const;
		int GetTextHeight(const std::string& text, int fontSize) const;



		// Static predefined colors for convenience
		static const SDL_Color WHITE;
		static const SDL_Color BLACK;
		static const SDL_Color RED;
		static const SDL_Color GREEN;
		static const SDL_Color BLUE;
		static const SDL_Color YELLOW;
	};
}


