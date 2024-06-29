#include<fstream>
#include<iostream>

#include "chip8.h"

void Chip8::initialize(void)
{

	cpu = new CPU();
	cpu->initialize();
	
	keyboard = new Keyboard();
	keyboard->initialize();

	display = new Display();
	display->initialize();

	audio = new Audio();
	audio->initialize();
	
}

void Chip8::loadROM(const char* pathname)
{
	// Open the ROM file in binary mode
	std::ifstream rom(pathname, std::ios::binary | std::ios::ate);
	if (!rom.is_open()) 
	{
		std::cerr << pathname << " does not exist." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Get the size of the ROM file
	auto filesize = rom.tellg();
	if (filesize > (MEMORY_SIZE - 0x200)) 
	{
		std::cerr << "ROM size exceeds available memory" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	// Read the ROM file into memory starting at address 0x200
	rom.seekg(0, std::ios::beg);
	rom.read(reinterpret_cast<char*>(memory + 0x200), size);
	rom.close();
}

void Chip8::loadFont(void)
{
	// According to Chip-8 specification, the fontset takes 80 bytes starting from 0x050 to 0x0A0.
	for (int i = 0; i < FONT_SIZE; i++)
	{
		cpu->setMemory(FONT_SIZE + i, display->getFont(i);
	}
}
