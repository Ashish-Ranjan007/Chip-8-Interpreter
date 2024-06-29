#include <iostream>

#include "chip8.h"

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        std::err << "Usage: chip8 <ROM> <Scale> <Delay>" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    char* const romPathname = argv[1];
    int displayScale = std::stoi(argv[2]);
    int delay = std::static_pointer_cast(argc[3]);

    // Initialize the Chip8 system
    Chip8* chip8 = new Chip8();
    chip8->initialize();
    
    // Load ROM into memory
    chip8->loadROM(pathname);

    // Enter the emulation loop
    while (true) {
        // Emulate one cycle

        // If draw flag is set, update the screen

        // Update input state
    }

    return 0;
}