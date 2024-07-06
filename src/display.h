#pragma once

#include <cstdint>

#include<SDL.h>

const int VRAM_SIZE = 32 * 64;
const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;

class Display
{

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	uint8_t vram[VRAM_SIZE];
	bool drawFlag;

public:
	Display(char* const title, int displayScale);
	~Display(void);
	void clearDisplay(void);
	uint8_t getPixel(int idx);
	void setPixel(int idx, uint8_t newValue);
	void render(void);
	bool getDrawFlag(void);
	void setDrawFlag(bool val);
};
