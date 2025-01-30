#pragma once

#include "Utillities/Vector2.h"
#include <functional>

struct SDL_Texture;
typedef unsigned int uint32_t;
struct SDL_Rect;
struct SDL_Point;
struct SDL_Renderer;

using Vector2F = Vector2<float>;
using Vector2I = Vector2<int>;


namespace ArksEngine
{
	class Core;

	class Texture
	{
		ArksEngine::Core* m_pOwner; // A ptr to the ArksEngine::Core
		const char* m_pFileName;  // A Path to the Actual image
		SDL_Texture* m_pTexture;  // Texture Ptr


	public:
		/**
		 * \brief 
		 * \param pRenderer A ptr to the ArksEngine::Renderer
		 * \param fileName  A Path to the Actual image
		 */
		Texture(ArksEngine::Core* pOwner, const char* fileName);

		// Create A new Texture
		Texture(ArksEngine::Core* pOwner);

		/**
		 * \brief This is a default Constructor
		 */
		~Texture() = default;

		/**
		 * \brief Draws the a specific part of the image
		 * \param source What part of image
		 * \param destination location
		 * \param dimensions width / height
		 */
		void RenderTexture(Vector2F source, Vector2F destination, Vector2F dimensions) const;

		/**
		 * \brief Draws the whole image
		 * \param destination location
		 * \param dimensions width / height
		 */
		void RenderTexture(Vector2F destination, Vector2F dimensions) const;

		//Renders texture at given point
		void RenderTexture(float x, float y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr) const;

		// Gets our actual texture
		[[nodiscard]] SDL_Texture* GetSDLTexture() const { return m_pTexture; }

		// Set out texture
		void SetTexture(SDL_Texture* newText) { m_pTexture = newText; }

		// Get information on pixels in textures
		void AccessPixels(const std::function<void(int x, int y, uint8_t r, uint8_t g, uint8_t b)>& pixelCallback) const;

		// Get Dimensions
		void GetDimensions(int& width, int& height) const;

	private:
		/**
		 * \brief Loads a image if image is already loaded it will just return that image
		 */
		void LoadNewTexture(SDL_Renderer* pRenderer);
	};

}



