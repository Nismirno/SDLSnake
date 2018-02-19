#pragma once
#ifndef _TEXTURE_H
#define _TEXTURE_H
#include <SDL.h>
#include <string>
#include <SDL_image.h>

#include "Globals.h"

class Texture {
public:
	// Initialize variables
	Texture();

	// Deallocate memory
	~Texture();

	// Loads image at specific path
	bool loadFromFile(std::string path, SDL_Renderer *renderer);

#ifdef _SDL_TTF_H
	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor,
	                          SDL_Renderer *renderer);
#endif // _SDL_TTF_H

	// Deallocate texture
	void free();

	// Set color modulation
	void setColor(uint8_t red, uint8_t green, uint8_t blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(uint8_t alpha);

	// Set dimensions
	void setDimensions(int w, int h);

	// Renders texture at given point
	void render(SDL_Renderer *renderer,
	            int x,
	            int y,
	            const SDL_Rect *clip = NULL,
	            double angle = 0.0,
	            const SDL_Point *center = NULL,
	            SDL_RendererFlip flip = SDL_FLIP_NONE) const;

	// Gets image dimension
	int getWidth() const;
	int getHeight() const;

	// Is texture loaded
	bool isLoaded() const;

private:
	// The actual hardware texture
	SDL_Texture *m_texture;

	// Image dimensions
	int m_width;
	int m_height;
};

#endif // !_TEXTURE_H

