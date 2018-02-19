#include "Texture.h"

Texture::Texture() {
	// Initialize
	m_texture = NULL;
	m_width = 0;
	m_height = 0;
}


Texture::~Texture() {
	// Deallocate
	free();
}


bool Texture::loadFromFile(std::string path, SDL_Renderer *renderer) {
	// Get rid of preexisting texture
	free();
	// The final texture
	SDL_Texture *newTexture = NULL;
	// Load image at specific path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	// Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	// Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	if (newTexture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s", path.c_str(), SDL_GetError());
		return false;
	}

	// Get image dimensions
	m_width = loadedSurface->w;
	m_height = loadedSurface->h;
	// Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
	// Return success
	m_texture = newTexture;
	return m_texture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor,
                                    SDL_Renderer *renderer) {
	// Get rid of preexisting texture
	free();
	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);

	if (textSurface == NULL) {
		printf("Unable to load text surface! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	// Create texture from surface pixels
	m_texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	if (m_texture == NULL) {
		printf("Unable to create texture from rendered font! SDL_ttf Error: %s\n", SDL_GetError());
		return false;
	}

	// Get image dimensions
	m_width = textSurface->w;
	m_height = textSurface->h;
	// Get rid of old surface
	SDL_FreeSurface(textSurface);
	return true;
}
#endif // !_SDL_TTF_H

void Texture::free() {
	// Free texture if it exists
	if (m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
		m_width = 0;
		m_height = 0;
	}
}


void Texture::setColor(uint8_t red, uint8_t green, uint8_t blue) {
	// Modulate textures
	SDL_SetTextureColorMod(m_texture, red, green, blue);
}


void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(m_texture, blending);
}


void Texture::setAlpha(uint8_t alpha) {
	SDL_SetTextureAlphaMod(m_texture, alpha);
}


void Texture::setDimensions(int w, int h) {
	m_width = w;
	m_height = h;
}


void Texture::render(SDL_Renderer *renderer, int x, int y,
                     const SDL_Rect *clip, double angle,
                     const SDL_Point *center, SDL_RendererFlip flip) const {
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, m_width, m_height };

	// Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, m_texture, clip, &renderQuad, angle, center, flip);
}


int Texture::getWidth() const {
	return m_width;
}


int Texture::getHeight() const {
	return m_height;
}


bool Texture::isLoaded() const {
	return m_texture != NULL;
}
