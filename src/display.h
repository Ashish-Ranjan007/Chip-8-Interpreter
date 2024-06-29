#pragma once

#include <cstdint>

const int VRAM_SIZE = 32 * 64;
const int FONT_SIZE = 80;

class Display
{

private:
	uint8_t vram[VRAM_SIZE];
	uint8_t fontset[FONT_SIZE];

public:
	void initialize(void);
	uint8_t getFont(uint8_t idx);

};
