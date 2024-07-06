#include <chrono>
#include <string>
#include <thread>
#include <iostream>

#include<SDL.h>

#include "chip8.h"

int main(int argc, char** argv)
{
    // Validate user input
    if (argc != 4)
    {
        std::cerr << "Usage: chip8 <ROM> <Scale> <Clock Speed> \n";
        std::cerr << "Arguments: \n";
        std::cerr << "  ROM: Path to the Chip8 ROM file.\n";
        std::cerr << "  Scale: Multiplier to scale the display size.\n";
        std::cerr << "  Clock Speed: CPU clock speed in Hz.\n";
        std::exit(EXIT_FAILURE);
    }

    // Parse user input
    char* const romPath = argv[1];
    int displayScale = std::stoi(argv[2]);
    int clockSpeed = std::stoi(argv[3]);

    // Initialize the Chip8 system
    Chip8* chip8 = new Chip8();
    chip8->initialize(romPath, displayScale);
    
    // Load ROM into memory
    chip8->loadROM(romPath);

    // Duration of each CPU cycle
    const int msPerCycle = 1000 / clockSpeed;

    bool quit = false;
    SDL_Event e;

    // Main / Application loop
    while (!quit) 
    {
        // Start the clock 
        auto start = std::chrono::high_resolution_clock::now();

        // Event Loop
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            } 
            else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            {
                chip8->keyboard->handleKeyEvent(e);
            }
        }

        // Run the cycle
        chip8->cpu->emulateCycle();

        // If drawFlag is set to true, render the frame buffer
        if (chip8->display->getDrawFlag())
        {
            chip8->display->render();
            chip8->display->setDrawFlag(false); // Reset drawFlag to false for the next cycle
        }

        // Record the time on clock up until this point
        auto end = std::chrono::high_resolution_clock::now();

        // Determine the duration of the current cycle
        std::chrono::duration<double, std::milli> elapsed = end - start;

        // If the duration of current cycle is less than the predefined duration for each cycle
        if (elapsed.count() < msPerCycle)
        {
            // Puts the thread to sleep
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(msPerCycle) - elapsed);
        }
    }

    return 0;
}
