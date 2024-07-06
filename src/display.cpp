#include<iostream>
#include<algorithm>

#include "display.h"

Display::Display(char* const title, int displayScale)
{
	if (
		SDL_CreateWindowAndRenderer(
		SCREEN_WIDTH * displayScale, 
		SCREEN_HEIGHT * displayScale, 
		0, &window, &renderer) < 0
	)
	{
		std::cerr << "Window or renderer could not be created. Error: " << SDL_GetError() << "\n";
		std::exit(EXIT_FAILURE);
	}

	texture = SDL_CreateTexture(
		renderer, 
		SDL_PIXELFORMAT_RGBA8888, 
		SDL_TEXTUREACCESS_STREAMING, 
		64, 
		32
	);
	if (texture == nullptr)
	{
		std::cerr << "Texture could not be created. Error: " << SDL_GetError() << "\n";
		std::exit(EXIT_FAILURE);
	}

	// Set window title
	SDL_SetWindowTitle(window, title);

	// Initialize VRAM
	for (int i = 0; i < VRAM_SIZE; i++)
	{
		vram[i] = 0;
	}

	// Initialize drawFlag
	drawFlag = false;
}

Display::~Display(void)
{
	delete[] vram;

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Display::clearDisplay(void)
{
	for (int i = 0; i < VRAM_SIZE; i++)
	{
		vram[i] = 0;
	}
}

uint8_t Display::getPixel(int idx)
{
	return vram[idx];
}

void Display::setPixel(int idx, uint8_t newValue)
{
	vram[idx] = newValue;
}

void Display::render(void)
{
	// Initialize a temporary frame buffer
	uint32_t pixels[64 * 32] = {};

	// XOR the vram into the temporary frame buffer
	for (int i = 0; i < 64 * 32; i++) {
		pixels[i] = (0xFFFFFF00 * vram[i]) | 0xFF; // White if pixel is 1, black if 0
	}

	// Render the frame buffer onto window
	SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

bool Display::getDrawFlag(void)
{
	return drawFlag;
}

void Display::setDrawFlag(bool val)
{
	drawFlag = val;
}

