#pragma once

#include "cpu.h";
#include "keyboard.h"
#include "display.h"
#include "audio.h"

class Chip8
{

private:
	CPU* cpu;
	Keyboard* keyboard;
	Display* display;
	Audio* audio;

public:
	void initialize(void);
	void loadROM(const char* pathname);
	void loadFont(void);
};
