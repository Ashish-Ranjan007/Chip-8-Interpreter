#include<fstream>
#include<iostream>
#include <SDL_mixer.h>

#include<SDL.h>

#include "chip8.h"

Chip8::Chip8() 
{
	keyboard = nullptr;
	display = nullptr;
	audio = nullptr;
	cpu = nullptr;

	// Initialize fontSet
	for (int i = 0; i < FONT_SIZE; i++)
	{
		fontSet[i] = FONT_SET[i];
	}
}

Chip8::~Chip8() 
{
	delete keyboard;
	delete display;
	delete audio;
	delete cpu;
	delete[] fontSet;

	cpu = nullptr;
	keyboard = nullptr;
	display = nullptr;
	audio = nullptr;

	SDL_Quit();
}

void Chip8::initialize(char* const title, int displayScale)
{
	// Initialize SDL subsystem
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
		std::exit(EXIT_FAILURE);
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr<<"SDL_mixer could not be initialized! SDL_mixer Error: "<< Mix_GetError()<<"\n";
		std::exit(EXIT_FAILURE);
	}

	// Initialize Chip8 system components
	display = new Display(title, displayScale);
	keyboard = new Keyboard();
	audio = new Audio();
	cpu = new CPU(audio, display, keyboard);

	// Load sound effect into system
	if (!audio->loadMedia())
	{
		std::cerr << "Sound effect could not be loaded! SDL_mixer Error: %s\n" << Mix_GetError() << "\n";
		std::exit(EXIT_FAILURE);
	}

}

void Chip8::loadROM(const char* pathname)
{
	// Open the ROM file in binary mode
	std::ifstream rom(pathname, std::ios::binary | std::ios::ate);
	if (!rom.is_open()) 
	{
		std::cerr<<"Error: " << pathname << " does not exist." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Get the size of the ROM file
	auto fileSize = rom.tellg();
	if (fileSize > (MEMORY_SIZE - 0x200)) 
	{
		std::cerr << "Error: ROM size exceeds available memory" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Store the ROM file in a buffer
	rom.seekg(0, std::ios::beg);
	char* buffer = new char[fileSize];
	rom.read(buffer, fileSize);
	
	// Read the ROM file into memory starting at address 0x200
	for (int i = 0; i < fileSize; ++i)
	{
		cpu->setMemory(0x200 + i, buffer[i]);
	}

	// Free buffers
	delete[] buffer;
}

void Chip8::loadFont(void)
{
	// According to Chip-8 specification, the fontSet takes 80 bytes starting from 0x050 to 0x0A0.
	for (uint16_t i = 0u; i < FONT_SIZE; i++)
	{
		cpu->setMemory(0x50u + i, fontSet[i]);
	}
}
