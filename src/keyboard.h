#pragma once

#include<cstdint>
#include<unordered_map>

#include <SDL.h>

class Keyboard
{

private:
	uint8_t keyboard[16];
	std::unordered_map<SDL_Keycode, uint8_t> keyMapping;

public:
	Keyboard(void);
	~Keyboard(void);
	uint8_t getKey(uint8_t key);
	void handleKeyEvent(const SDL_Event& e);
};