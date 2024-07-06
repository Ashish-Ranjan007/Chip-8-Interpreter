#include<iostream>

#include "keyboard.h"


Keyboard::Keyboard(void)
{

    /*
    * Key mappings for a modern keyboard

        1  2  3  C          1  2  3  4

        4  5  6  D          q  w  e  r
                      =>
        7  8  9  E          a  s  d  f

        A  0  B  F          z  x  c  v

    */

    // Initialize keyMappings
    keyMapping[SDLK_1] = 0x1; // 1
    keyMapping[SDLK_2] = 0x2; // 2
    keyMapping[SDLK_3] = 0x3; // 3
    keyMapping[SDLK_4] = 0xC; // 4

    keyMapping[SDLK_q] = 0x4; // q
    keyMapping[SDLK_w] = 0x5; // w
    keyMapping[SDLK_e] = 0x6; // e
    keyMapping[SDLK_r] = 0xD; // r

    keyMapping[SDLK_a] = 0x7; // a
    keyMapping[SDLK_s] = 0x8; // s
    keyMapping[SDLK_d] = 0x9; // d
    keyMapping[SDLK_f] = 0xE; // f

    keyMapping[SDLK_z] = 0xA; // z
    keyMapping[SDLK_x] = 0x0; // x
    keyMapping[SDLK_c] = 0xB; // c
    keyMapping[SDLK_v] = 0xF; // v

    // Initialize keyboard state
    for (int i = 0; i < 16; i++)
    {
        keyboard[i] = 0;
    }
}

Keyboard::~Keyboard(void)
{
    delete[] keyboard;
}

uint8_t Keyboard::getKey(uint8_t key)
{
	return keyboard[key];
}

void Keyboard::handleKeyEvent(const SDL_Event& e) {
    // Map SDL keycodes to CHIP-8 keys
    auto it = keyMapping.find(e.key.keysym.sym);

    if (it != keyMapping.end()) {
        uint8_t chip8Key = it->second;

        if (e.type == SDL_KEYDOWN) {
            keyboard[chip8Key] = 1;
        }
        else if (e.type == SDL_KEYUP) {
            keyboard[chip8Key] = 0;
        }
    }
}
